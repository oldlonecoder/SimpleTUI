//
// Created by oldlonecoder on 11/20/23.
//

//#ifndef SIMPLETUI_KEYDATA_H
//#define SIMPLETUI_KEYDATA_H
#pragma once

#include "SimpleTUI/Exports.h"

#include <string_view>
#include <AppBook/Book/AppBook.h>


namespace Tui::IO
{


struct STUI_EXPORT KeyData
{
    enum enumerated
    {
        Null,
        F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12,
        ArrowUpCtrl,
        ArrowDownCtrl,
        ArrowRightCtrl,
        ArrowLeftCtrl,
        ArrowUp,
        ArrowDown,
        ArrowRight,
        ArrowLeft,
        ArrowUpAlt,
        ArrowDownAlt,
        ArrowRightAlt,
        ArrowLeftAlt,
        ArrowUpCtrlAlt,
        ArrowDownCtrlAlt,
        ArrowRightCtrlAlt,
        ArrowLeftCtrlAlt,
        ArrowUpShiftCtrl,
        ArrowDownShiftCtrl,
        ArrowRightShiftCtrl,
        ArrowLeftShiftCtrl,
        Ins, Home, PgUp, Del, End, PgDn,
        CtrlAltIns,
        CtrlAltHome,
        CtrlAltPgUp,
        CtrlAltDel,
        CtrlAltEnd,
        CtrlAltPgDn,
        CtrlIns,
        CtrlHome,
        CtrlPgUp,
        CtrlDel,
        CtrlEnd,
        CtrlPgDn,
        ShiftF1,
        ShiftF2,
        ShiftF3,
        ShiftF4,
        ShiftF5,
        ShiftF6,
        ShiftF7,
        ShiftF8,
        ShiftF9,
        ShiftF10,
        ShiftF11,
        ShiftF12,
        ShiftEnter,
        AltEnter
    };
    enum state : uint8_t {
        CTRL = 1,
        WIN = 2,
        SHIFT = 4,
        ALT = 8
    };
    static constexpr std::string_view OptWinPrefix = "\x18\x40\x73";
    static constexpr std::string_view MetaPrefix = "\x1b";


    struct STUI_EXPORT Data
    {
        std::string_view Name; ///< key's name  ex.: "CTRL+1"
        KeyData::enumerated Enum; ///< key mnemonic
        std::string_view Seq;  ///< Input Data

    };

    static std::vector<KeyData::Data> KeyDB;

    static KeyData::Data const& Scan(uint8_t const* instr);
    static bool IsMeta(uint8_t const* instr);
    static bool ESCKey(uint8_t const* instr);


};

}
//#endif //SIMPLETUI_KEYDATA_H
