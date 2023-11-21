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
                 "ControlBase",
                 {
                     {State::Active,    {Color::HotPink4,Color::Grey27}},
                     {State::Disable,   {Color::Grey19, Color::Grey35}},    // Keep coherance with widget base
                     {State::Normal,    {Color::Blue,Color::Grey27}},
                     {State::Focus,     {Color::Red4, Color::Grey27}},
                     {State::Error,     {Color::Red4, Color::Grey27}},
                     {State::Warning,   {Color::Red4, Color::Yellow}},
                     {State::Illegal,   {Color::Red4, Color::DarkBlue}},
                     {State::Invalid,  {Color::Grey89, Color::Red}},
                     {State::Visible,  {Color::Reset, Color::Reset}},
                     {State::Success,  {Color::Lime, Color::DarkGreen}},
                     {State::Pressed,  {Color::Blue, Color::Grey27}},

                 }
             },
             {
                 "shortkey",
                 {
                     {State::Active,    {Color::HotPink4,Color::Grey27}},
                     {State::Disable,   {Color::Grey19, Color::Grey35}},    // Keep coherance with widget base
                     {State::Normal,    {Color::Blue,Color::Grey27}},
                     {State::Focus,     {Color::Red4, Color::Grey27}},
                     {State::Error,     {Color::Red4, Color::Grey27}},
                     {State::Warning,   {Color::Red4, Color::Yellow}},
                     {State::Illegal,   {Color::Red4, Color::DarkBlue}},
                     {State::Invalid,  {Color::Grey89, Color::Red}},
                     {State::Visible,  {Color::Reset, Color::Reset}},
                     {State::Success,  {Color::Lime, Color::DarkGreen}},
                     {State::Pressed,  {Color::Blue, Color::Grey27}},
                 }
             },
             {
                 "input-area", // widget::text_input
                 {
                     {State::Active,    {Color::HotPink4,Color::Grey27}},
                     {State::Disable,   {Color::Grey19, Color::Grey35}},    // Keep coherance with widget base
                     {State::Normal,    {Color::Blue,Color::Grey27}},
                     {State::Focus,     {Color::Red4, Color::Grey27}},
                     {State::Error,     {Color::Red4, Color::Grey27}},
                     {State::Warning,   {Color::Red4, Color::Yellow}},
                     {State::Illegal,   {Color::Red4, Color::DarkBlue}},
                     {State::Invalid,  {Color::Grey89, Color::Red}},
                     {State::Visible,  {Color::Reset, Color::Reset}},
                     {State::Success,  {Color::Lime, Color::DarkGreen}},
                     {State::Pressed,  {Color::Blue, Color::Grey27}},
                 }
             },
             {
                 "input-field",
                 {
                     {State::Active,    {Color::HotPink4,Color::Grey27}},
                     {State::Disable,   {Color::Grey19, Color::Grey35}},    // Keep coherance with widget base
                     {State::Normal,    {Color::Blue,Color::Grey27}},
                     {State::Focus,     {Color::Red4, Color::Grey27}},
                     {State::Error,     {Color::Red4, Color::Grey27}},
                     {State::Warning,   {Color::Red4, Color::Yellow}},
                     {State::Illegal,   {Color::Red4, Color::DarkBlue}},
                     {State::Invalid,  {Color::Grey89, Color::Red}},
                     {State::Visible,  {Color::Reset, Color::Reset}},
                     {State::Success,  {Color::Lime, Color::DarkGreen}},
                     {State::Pressed,  {Color::Blue, Color::Grey27}},
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