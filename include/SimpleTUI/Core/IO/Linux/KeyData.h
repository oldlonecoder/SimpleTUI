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
        Text,
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

    uint8_t Meta :1;
    uint8_t Ctrl :1;
    uint8_t Shift :1;
    uint8_t Alt :1;

    static constexpr std::string_view OptWinPrefix = "\x18\x40\x73";
    static constexpr std::string_view MetaPrefix = "\x1b";


    struct STUI_EXPORT MetaData
    {
        std::string_view Name; ///< key's name  ex.: "CTRL+1"
        KeyData::enumerated Enum; ///< key mnemonic
        std::string_view Seq;  ///< Input MetaData

    };



    static std::vector<KeyData::MetaData> KeyDB;

    static KeyData::MetaData const& Scan(const char* instr);
    static bool IsMeta(char const* instr);
    static bool ESCKey(char const* instr);

    union {
        KeyData::MetaData M;
        std::string Seq;
    };
    KeyData(){}
    ~KeyData();
    explicit KeyData(KeyData::MetaData M);
    explicit KeyData(std::string Seq);
    static Book::Action KeyInDelegate(std::string_view);
};

}
//#endif //SIMPLETUI_KEYDATA_H
