//
// Created by oldlonecoder on 11/20/23.
//

#include "SimpleTUI/Ui/UiControl.h"

namespace Tui
{


//UiControl::~UiControl()
//{
//
//}

UiControl::UiControl(Object *ParentObj, const std::string& ID, wclass::Type WC):DisplayMem(ParentObj, ID){}

Book::Result UiControl::Render(Rect R)
{
    return DisplayMem::Render(R);
}

Book::Result UiControl::Allocate(Dim DXY)
{
    return DisplayMem::Allocate(DXY);
}

Book::Result UiControl::Render()
{
    return DisplayMem::Render();
}

Book::Result UiControl::Allocate()
{
    return DisplayMem::Allocate();
}

void UiControl::AssignColors()
{
    DisplayMem::AssignColors();
}
} // Tui