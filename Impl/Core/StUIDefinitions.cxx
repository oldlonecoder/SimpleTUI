//
// Created by oldlonecoder on 11/20/23.
//

#include "SimpleTUI/Core/StUIDefinitions.h"

namespace Tui
{


ColorDB::Themes ColorDB::ColorDBData =
{
     {
         "default",
         {
             {
                 "default",
                 {
                     {State::Active, {Color::HotPink4,Color::Grey27}},
                     {State::Disable,{Color::Grey19, Color::Grey35}},    // Keep coherance with widget base
                     {State::Normal,{Color::Grey70,Color::Grey27}},
                     {State::Focus,{Color::Red4, Color::Grey27}}
                 }
             },
             {
                 "shortkey",
                 {
                     {State::Active, {Color::HotPink4,Color::Grey27}},
                     {State::Disable,{Color::Grey19, Color::Grey35}},    // Keep coherance with widget base
                     {State::Normal,{Color::Grey70,Color::Grey27}},
                     {State::Focus,{Color::Red4, Color::Grey27}}
                 }
             },
             {
                 "input-area", // widget::text_input
                 {
                     {State::Active, {Color::White, Color::Grey30}},    // Keep coherance with widget base
                     {State::Disable,{Color::Grey39, Color::Grey35}},
                     {State::Normal,{Color::Grey37, Color::Grey30}},
                     {State::Focus,{Color::White, Color::Grey30}}
                 }
             },
             {
                 "input-field",
                 {
                     {State::Active, {Color::Grey70, Color::Grey27}},    // Keep coherance with widget base
                     {State::Disable, {Color::Grey39, Color::Grey35}},
                     {State::Normal, {Color::Grey70, Color::Grey27}},
                     {State::Focus, {Color::White, Color::Grey27}}
                 }
             }
         }
     }
 };



/*!
 * @brief
 * @param ElementID
 * @return  Map of the Element's Color::Pairs
 */
ColorDB::Components const &ColorDB::Element(std::string_view ElementID)
{
    auto& Theme = ColorDB::ColorDBData["default"];
    return Theme[ElementID];
}

}