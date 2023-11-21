//
// Created by oldlonecoder on 11/20/23.
//

#include "SimpleTUI/Core/Screen.h"


#if defined(_WIN32)
#define WIN32_LEAN_AND_MEAN
#define VC_EXTRALEAN
#   include <Windows.h>
#   include <stdlib.h>
#   include <io.h>
#   define write _write
#elif defined(__linux__)
#   include <sys/ioctl.h>
#   include <unistd.h>
#endif


namespace Tui
{




Screen::ScreenArrayT Screen::ScreenArray;



Screen::Screen(const std::string& ID):DisplayMem(nullptr,ID)
{
    Screen::ScreenArray[Id()] = this;
}

Screen::~Screen()
{

}

Book::Result Screen::Init()
{

#if defined(_WIN32)
    CONSOLE_SCREEN_BUFFER_INFO csbi;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &csbi);
    Dimensions = {
            1,1,
            {static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1), static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)},
            {static_cast<int>(csbi.srWindow.Right - csbi.srWindow.Left + 1), static_cast<int>(csbi.srWindow.Bottom - csbi.srWindow.Top + 1)}
    };

#elif defined(__linux__)
    winsize win{};
    ioctl(fileno(stdout), TIOCGWINSZ, &win);
    Dimensions = {
        static_cast<int>(win.ws_col), static_cast<int>(win.ws_row),
        {static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)},{static_cast<int>(win.ws_col), static_cast<int>(win.ws_row)}
    };

#endif // Windows/Linux

    AppBook::Debug() << " ScreenSize: " << Color::Yellow << (std::string)Dimensions;


    Allocate(Dimensions);
    Clear({});
    return Book::Result::Ok;
}

Screen &Screen::GetScreen(const std::string &ScrID)
{
    return *Screen::ScreenArray[ScrID];
}

std::size_t Screen::DoUpdates()
{
    if(UpdatesQueu.empty())
        return 0;
    auto sz = UpdatesQueu.size();
    for(auto &U : UpdatesQueu)
    {
        Rect R = U.R / Geometry();
        if(!R) continue;
        U.D->Render(R);
    }
    return  sz;
}


Screen& Screen::GotoXY(Point Pt)
{
    if(!Rect({}, Dimensions)[Pt])
    {
        AppBook::Error() << Book::Result::Rejected << " coord '" << Pt << "' is out of the Screen's boundaries.";
        return *this;
    }

    std::cout << "\x1b[" << Pt.Y + 1 << ';' << Pt.X + 1 << 'H';
    fflush(stdout);
    CursorPos = Pt;
    return *this;
}


} // Tui