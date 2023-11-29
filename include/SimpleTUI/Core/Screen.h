//
// Created by oldlonecoder on 11/20/23.
//

//#ifndef SIMPLETUI_SCREEN_H
//#define SIMPLETUI_SCREEN_H
/******************************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                                        *
 *   serge.lussier@oldlonecoder.club                                                      *
 *                                                                                        *
 *                                                                                        *
 *   Unless otherwise specified, all code IsIn this project is written                      *
 *   by the author (Serge Lussier)                                                        *
 *   and no one else then not even {copilot, chatgpt, or any other AI calamities}         *
 *   ----------------------------------------------------------------------------------   *
 *   Copyrights from authors other than Serge Lussier also apply here                     *
 *   Open source FREE licences also apply To the code from the same author (Serge Lussier)*
 *   ----------------------------------------------------------------------------------   *
 ******************************************************************************************/

#pragma once
#include "SimpleTUI/Core/DisplayMem.h"
#if defined(_MSC_VER) || defined(WIN64) || defined(_WIN64) || defined(__WIN64__) || defined(WIN32) || defined(_WIN32) || defined(__WIN32__) || defined(__NT__)
#error   This version is early devel and only on Linux for now.
//#include "windows"
#elif defined(__linux__)
#include "SimpleTUI/Core/IO/Linux/ConIO.h"
#endif
#include <stack>


namespace Tui
{



/*!
 * @brief this is the Console Visual Control.
 *
 * All "UiControls" including TopLevel [floating] Controls (aka Windows) are children of this instance of Screen.
 */
class STUI_EXPORT Screen : protected DisplayMem
{

    Point CursorPos{};
#if defined(__linux__)
    IO::ConIO ConIO;
#endif

    using ScreenArrayT = std::map<std::string, Screen*>;
    static ScreenArrayT ScreenArray;

    struct UpdateNode
    {
        DisplayMem* D{nullptr};
        Rect        R;
        using Queu = std::vector<UpdateNode>;
        //...
    };

    Screen::UpdateNode::Queu UpdatesQueu;
    std::size_t DoUpdates();

public:

    using String = std::vector<DisplayMem::Char>;

    Screen() = default;
    explicit Screen(const std::string& ID);
    ~Screen() override;

    Screen& Create(const std::string& ScreenName);

    Book::Result Setup();
    static Screen& GetScreen(const std::string& ScrID);

    Screen& GotoXY(Point Pt);

    [[maybe_unused]] static void EndStr(Screen::String& Str);
    Book::Result Update(Rect SubRect);
    Book::Result Update(DisplayMem* Dm, Rect SubRect);



};

} // Tui

//#endif //SIMPLETUI_SCREEN_H
