//
// Created by oldlonecoder on 11/19/23.
//

//#ifndef SIMPLETUI_DEVTEST_H
//#define SIMPLETUI_DEVTEST_H
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

#include "SimpleTUI/Core/IO/Linux/ConIO.h"



namespace Tui::Test
{

class DevTest : public Util::Object
{

    Tui::IO::ConIO ConIO;

public:
    DevTest(std::string ID);
    ~DevTest() override;


    auto Exec()->Book::Result;



};

} // Tui::Test

//#endif //SIMPLETUI_DEVTEST_H
