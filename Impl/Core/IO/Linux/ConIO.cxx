/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/

#include "SimpleTUI/Core/IO/Linux/ConIO.h"
#include <sys/ioctl.h>
#include <unistd.h>

#include "SimpleTUI/Core/Screen.h"

namespace Tui::IO
{




ConIO* ConIOInstance = nullptr;






/*!
 * \brief ConIO::key_in read the console input buffer in raw mode.
 * \param fd reference to the instance of ifd this ConIO is notified.
 *
 * \note if input pksize > 6 then there is buffer overflow - bail and reject.
 *
 * \return instance of expect<>: rem::rejected to stop this thread io_loop, or rem::accepted to let the io_loop continue to wait/read keys input
 * \author &copy;2023, oldlonecoder/Serge Lussier  (serge.lussier@oldlonecoder.club)
 */
Book::Action ConIO::key_in(ifd &fd)
{

// 1: check packet size ( p > 0, p <= 6 )
    if(fd.pksize > 9)
        throw AppBook::Exception()[AppBook::Except() << Book::Result::Rejected << "  - Unexpected packet size larger than 9 bytes.[" << fd.pksize << "]"];


    //let's do some debugs:
    StrAcc msg = "input ";
    msg << Color::Yellow , fd.pksize , Color::Reset , " bytes in: {\"KeyText\", KeyData::Mnemonic,  \"";

    //format :
    const char* fmt = "\\x%02X";
    if((fd.pksize == 1) && (fd.internal_buffer[0] == 27))
    {
        AppBook::Message() << Color::White << "[ESC] " << Color::Reset <<"pressed - Terminating the ConIO loop!";
        return Book::Action::End;
    }

    // Get the key sequence data:
    char keyseq[10]={}; // I think the compiler fills in with zero's
    std::size_t x = 0;
    for(; x< fd.pksize; x++)
    {
        char c= fd.internal_buffer[x];
        msg << fmt << c;
        keyseq[x] = c;
    }
    keyseq[fd.pksize] = 0; // Never know if keyseq[]={} does not fill with 0's...
    auto e = kbhit_notify(keyseq);
    // ...
    std::string Str = keyseq;
    AppBook::Info() <<  Color::Yellow << msg << Color::Reset << "\"},";

    if(auto KD = KeyData::Scan(Str.c_str()); KD.Enum != KeyData::Null)
        AppBook::Debug() << "Key Input Details:" << Color::Yellow << KD.Name;
    else
        AppBook::Debug() << "No Key MetaData for :" << Color::Yellow << msg;
    return Book::Action::Continue;
}

Book::Action ConIO::idle()
{
    return _idle_signal();
}


[[maybe_unused]] ConIO::ConIO(Util::Object *parent_obj, const std::string& cid): Util::Object(parent_obj, cid) { }

//ConIO::~ConIO()
//{
//    //???
//}


/*!
 * \brief ConIO::begin ConIO initializing routine.
 *
 *     Creates the input-loop thread.
 *
 * \return
 */
Book::Result ConIO::Start()
{
    struct winsize win;

    auto TermColors = StrAcc::Make(std::getenv("COLORTERM"));
    if(!TermColors)
        TermColors = StrAcc::Make(std::getenv("TERM"));

    if((!TermColors["24bit"]) && (!TermColors["truecolor"]) && (!TermColors["256"]))
        AppBook::Warning() << " SimpleTUI requires to be running on a minimum of UTF-8 Fonts and 256 colors or [24bits] truecolor term based terminal! ";

    AppBook::Info() << " Terminal colors from ENV: " << TermColors;

    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    tcgetattr(STDIN_FILENO, &con);
    raw = con;
    raw.c_iflag &= ~( BRKINT | PARMRK |ISTRIP);
    raw.c_iflag &= ~(PARMRK);
    raw.c_cflag |= (CS8|IGNBRK);
    raw.c_lflag &= ~(ICANON | ECHO | IEXTEN | TOSTOP);

    raw.c_cc[VMIN] = 0;
    raw.c_cc[VTIME] = 1;
    raw.c_cc[VSTART] = 0;
    raw.c_cc[VSTOP] = 0;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &raw);
        //... To be continued

#if defined(_WIN32)
    #error   This version is early devel and only on Linux for now.
//    CONSOLE_SCREEN_BUFFER_INFO csbi;
//    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
//    Dimensions = {
//            1,1,
//            {static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1), static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)},
//            {static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1), static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)}
//    };

#elif defined(__linux__)
    winsize win{};
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    WH = {
        static_cast<int>(win.ws_col), static_cast<int>(win.ws_row),
        {static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)},{static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)}
    };

#else  // Linux
#error This version is early devel and only on Linux for now.
#endif

    io_listener = listener(this, 1000);
    (void)io_listener.add_ifd(STDIN_FILENO, ifd::O_READ| ifd::I_AUTOFILL);
    auto i = io_listener.query_fd(STDIN_FILENO);
    i->read_signal.Connect(this, &ConIO::key_in);
    io_listener.idle_signal().Connect(this, &ConIO::idle);
    kbhit_notifier.Connect(&KeyData::KeyInDelegate);

    AppBook::Info() << Color::DarkGreen << "starting the io loop thread :";
    io_thread = std::thread([this](){
        auto e = io_listener.run();
        //... dependant du code de retour ...

        // ...
    });

    return Book::Result::Ok;
}

Book::Result ConIO::Terminate()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &con);
    RestoreScreen();
    return Book::Result::Ok;
}

void ConIO::operator()()
{

}


void ConIO::Clear()
{
    std::cout << "\x1b[2K" << std::flush;
}

void ConIO::GotoXY(Point Pt)
{
    std::cout << "\033[" << Pt.Y + 1 << ';' << Pt.X + 1 << 'H' << std::flush;
}

void ConIO::ToLineEnd()
{

}


void ConIO::ToLineStart()
{
    std::cout << "\r" << std::flush;
}

void ConIO::Underline(bool On)
{
    std::string Str = On ? "\x1B[4m" : "\x1B[24m";
    std::cout << Str << std::flush;
}

void ConIO::DoubleUnderline(bool On)
{
    std::string Str = On ? "\x1B[21m" : "\x1B[24m";
    std::cout << Str << std::flush;
}



void ConIO::RestoreScreen()
{
    std::cout << "\x1b[?47l\x1b[0m\x1b[?1049l\x1b[u" << std::flush;
}

void ConIO::SaveScreen()
{
    std::cout << "\x1b[s\x1b[?47h\x1b[0m\x1b[?1049h" << std::flush;
}

ConIO &ConIO::Instance()
{
    if(!ConIOInstance)
        throw AppBook::Exception()[ AppBook::Fatal() << "ConIO has no instance yet. Contruct by using IO::ConIO::Construct( Object* ParentObj,. const std::string& ConsoleID"];

    return *ConIOInstance;
}

ConIO &ConIO::Construct(Object *ParentObj, const std::string &ConID)
{
    if(ConIOInstance)
        return *ConIOInstance;

    ConIOInstance = new ConIO(ParentObj, ConID);
    return *ConIOInstance;
}


}