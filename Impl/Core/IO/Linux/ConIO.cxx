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


namespace Tui::IO
{

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

ConIO::ConIO(): Util::Object(nullptr, "ConIO") { }

[[maybe_unused]] ConIO::ConIO(Util::Object *parent_obj): Util::Object(parent_obj, "ConIO") { }

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

    AppBook::Info() << " Terminal Colors Info: " << TermColors;

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
    io_thread.join(); // Bloc Here for now.

    return Book::Result::Ok;
}

Book::Result ConIO::Terminate()
{
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &con);
    return Book::Result::Ok;
}

void ConIO::operator()()
{

}

void ConIO::Clear()
{
    std::cout << "\x1b[2K" << std::flush;
}

void ConIO::GotoXY()
{

}

void ConIO::ToLineEnd()
{

}

void ConIO::ToLineStart()
{
    std::cout << "\r" << std::flush;
}


}