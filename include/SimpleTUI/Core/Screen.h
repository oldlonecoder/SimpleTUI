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
#include <stack>


namespace Tui
{

class STUI_EXPORT Screen : public DisplayMem
{

    using ScreenArrayT = std::map<std::string, Screen*>;
    static ScreenArrayT ScreenArray;

    struct UpdateNode
    {
        DisplayMem* D{nullptr};
        Rect        R;
        using Queu = std::stack<UpdateNode>;
        //...
    };

    Screen::UpdateNode::Queu UpdatesQueu;

    std::size_t DoUpdates();


public:

    Screen() = default;
    explicit Screen(const std::string& ID);
    ~Screen() override;

    Book::Result Init();

    static Screen& GetScreen(const std::string& ScrID);



};

} // Tui

//#endif //SIMPLETUI_SCREEN_H
