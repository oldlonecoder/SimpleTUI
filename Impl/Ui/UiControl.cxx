//
// Created by oldlonecoder on 11/20/23.
//

#include "SimpleTUI/Ui/UiControl.h"

namespace Tui
{


UiControl::~UiControl()
{
    ;
}

UiControl::UiControl(Object *ParentObj, const std::string& ID, wclass::Type WC):DisplayMem(ParentObj, ID)
{

}
} // Tui