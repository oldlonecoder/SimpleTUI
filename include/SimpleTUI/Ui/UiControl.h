//
// Created by oldlonecoder on 11/20/23.
//

//#ifndef SIMPLETUI_UICONTROL_H
//#define SIMPLETUI_UICONTROL_H
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


namespace Tui
{

class STUI_EXPORT UiControl : public DisplayMem
{
public:
    UiControl() = default;
    ~UiControl() override = default;

    UiControl(Object* ParentObj, const std::string& ID, wclass::Type WC=wclass::Child);

protected:
     Book::Result Render(Rect R) override;
     Book::Result Allocate(Dim DXY) override;
     Book::Result Render() override;
     Book::Result Allocate() override;
     void AssignColors() override;
};

} // Tui

//#endif //SIMPLETUI_UICONTROL_H
