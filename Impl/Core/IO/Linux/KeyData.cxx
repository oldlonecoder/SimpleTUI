//
// Created by oldlonecoder on 11/20/23.
//

#include <utility>

#include "SimpleTUI/Core/IO/Linux/KeyData.h"



namespace Tui::IO
{

KeyData::MetaData NullKey{"Null",            KeyData::Null,                          ""};


std::vector<KeyData::MetaData> KeyData::KeyDB =
{
    // Arrow:
    {"Alt+Enter",       KeyData::AltEnter,                      "\x1b\x0A"},
    {"Shift+Enter",     KeyData::ShiftEnter,                    "\x1B\x4F\x4D"},
    {"Ctrl+ArrowUp",    KeyData::ArrowUpCtrl,                   "\x1B\x5B\x31\x3B\x35\x41"},
    {"Ctrl+ArrowDown",  KeyData::ArrowDownCtrl,                 "\x1B\x5B\x31\x3B\x35\x42"},
    {"Ctrl+ArrowRight", KeyData::ArrowRightCtrl,                "\x1B\x5B\x31\x3B\x35\x43"},
    {"Ctrl+ArrowLeft",  KeyData::ArrowLeftCtrl,                 "\x1B\x5B\x31\x3B\x35\x44"},
    {"Alt+ArrowUp",     KeyData::ArrowUpAlt,                    "\x1B\x5B\x31\x3B\x33\x41"},
    {"Alt+ArrowDown",   KeyData::ArrowDownAlt,                  "\x1B\x5B\x31\x3B\x33\x42"},
    {"Alt+ArrowRight",  KeyData::ArrowRightAlt,                 "\x1B\x5B\x31\x3B\x33\x43"},
    {"Alt+ArrowLeft",   KeyData::ArrowLeftAlt,                  "\x1B\x5B\x31\x3B\x33\x44"},
    {"Ctrl+Shift+ArrowUp",     KeyData::ArrowUpShiftCtrl,       "\x1B\x5B\x31\x3B\x36\x41"},
    {"Ctrl+Shift+ArrowDown",   KeyData::ArrowDownShiftCtrl,     "\x1B\x5B\x31\x3B\x36\x42"},
    {"Ctrl+Shift+ArrowRight",  KeyData::ArrowRightShiftCtrl,    "\x1B\x5B\x31\x3B\x36\x43"},
    {"Ctrl+Shift+ArrowLeft",   KeyData::ArrowLeftShiftCtrl,     "\x1B\x5B\x31\x3B\x36\x44"},
    {"Ctrl+Alt+ArrowUp",     KeyData::ArrowUpCtrlAlt,           "\x1B\x5B\x31\x3B\x37\x41"},
    {"Ctrl+Alt+ArrowDown",   KeyData::ArrowDownCtrlAlt,         "\x1B\x5B\x31\x3B\x37\x42"},
    {"Ctrl+Alt+ArrowRight",  KeyData::ArrowRightCtrlAlt,        "\x1B\x5B\x31\x3B\x37\x43"},
    {"Ctrl+Alt+ArrowLeft",   KeyData::ArrowLeftCtrlAlt,         "\x1B\x5B\x31\x3B\x37\x44"},
    {"ArrowUp",         KeyData::ArrowUp,                       "\x1B\x5B\x41"},
    {"ArrowDown",       KeyData::ArrowDown,                     "\x1B\x5B\x42"},
    {"ArrowRight",      KeyData::ArrowRight,                    "\x1B\x5B\x43"},
    {"ArrowLeft",       KeyData::ArrowLeft,                     "\x1B\x5B\x44"},
    {"Insert",          KeyData::Ins,                           "\x1B\x5B\x32\x7E"},
    {"Home",            KeyData::Home,                          "\x1B\x5B\x48"},
    {"PgUp",            KeyData::PgUp,                          "\x1B\x5B\x35\x7E"},
    {"Del",             KeyData::Del,                           "\x1B\x5B\x33\x7E"},
    {"End",             KeyData::End,                           "\x1B\x5B\x46"},
    {"PgDn",            KeyData::PgDn,                          "\x1B\x5B\x36\x7E"},
    {"Ctrl+Alt+Insert", KeyData::CtrlAltIns,                    "\x1B\x5B\x32\x3B\x33\x7E"},
    {"Ctrl+Alt+Home",   KeyData::CtrlAltHome,                   "\x1B\x5B\x31\x3B\x33\x48"},
    {"Ctrl+Alt+PgUp",   KeyData::CtrlAltPgUp,                   "\x1B\x5B\x35\x3B\x33\x7E"},
    {"Ctrl+Alt+Del",    KeyData::CtrlAltDel,                    "\x1B\x5B\x33\x3B\x33\x7E"},
    {"Ctrl+Alt+End",    KeyData::CtrlAltEnd,                    "\x1B\x5B\x31\x3B\x33\x46"},
    {"Ctrl+Alt+PgDn",   KeyData::CtrlAltPgDn,                   "\x1B\x5B\x36\x3B\x33\x7E"},
    {"Ctrl+Insert",     KeyData::CtrlIns,                       "\x1B\x5B\x32\x3B\x35\x7E"},
    {"Ctrl+Home",       KeyData::CtrlHome,                      "\x1B\x5B\x31\x3B\x35\x48"},
    {"Ctrl+PgUp",       KeyData::CtrlPgUp,                      "\x1B\x5B\x35\x3B\x35\x7E"},
    {"Ctrl+Del",        KeyData::CtrlDel,                       "\x1B\x5B\x33\x3B\x35\x7E"},
    {"Ctrl+End",        KeyData::CtrlEnd,                       "\x1B\x5B\x31\x3B\x35\x46"},
    {"Ctrl+PgDn",       KeyData::CtrlPgDn,                      "\x1B\x5B\x36\x3B\x35\x7E"},
    {"F1",              KeyData::F1,                            "\x1B\x4F\x50"},
    {"F2",              KeyData::F2,                            "\x1B\x4F\x51"},
    {"F3",              KeyData::F3,                            "\x1B\x4F\x52"},
    {"F4",              KeyData::F4,                            "\x1B\x4F\x53"},
    {"F5",              KeyData::F5,                            "\x1B\x5B\x31\x35\x7E"},
    {"F6",              KeyData::F6,                            "\x1B\x5B\x31\x37\x7E"},
    {"F7",              KeyData::F7,                            "\x1B\x5B\x31\x38\x7E"},
    {"F8",              KeyData::F8,                            "\x1B\x5B\x31\x39\x7E"},
    {"F9",              KeyData::F9,                            "\x1B\x5B\x32\x30\x7E"},
    {"F10",             KeyData::F10,                           "\x1B\x5B\x32\x31\x7E"},
    {"F11",             KeyData::F11,                           "\x1B\x5B\x32\x33\x7E"},
    {"F12",             KeyData::F12,                           "\x1B\x5B\x32\x34\x7E"},
    {"Shift+F1",        KeyData::ShiftF1,                       "\x1B\x4F\x32\x50"},
    {"Shift+F2",        KeyData::ShiftF2,                       "\x1B\x4F\x32\x51"},
    {"Shift+F3",        KeyData::ShiftF3,                       "\x1B\x4F\x32\x52"},
    {"Shift+F4",        KeyData::ShiftF4,                       "\x1B\x4F\x32\x53"},
    {"Shift+F5",        KeyData::ShiftF5,                       "\x1B\x5B\x31\x35\x3B\x32\x7E"},
    {"Shift+F6",        KeyData::ShiftF6,                       "\x1B\x5B\x31\x37\x3B\x32\x7E"},
    {"Shift+F7",        KeyData::ShiftF7,                       "\x1B\x5B\x31\x38\x3B\x32\x7E"},
    {"Shift+F8",        KeyData::ShiftF8,                       "\x1B\x5B\x31\x39\x3B\x32\x7E"},
    {"Shift+F9",        KeyData::ShiftF9,                       "\x1B\x5B\x32\x30\x3B\x32\x7E"},
    {"Shift+F10",       KeyData::ShiftF10,                      "\x1B\x5B\x32\x31\x3B\x32\x7E"},
    {"Shift+F11",       KeyData::ShiftF11,                      "\x1B\x5B\x32\x33\x3B\x32\x7E"},
    {"Shift+F12",       KeyData::ShiftF12,                      "\x1B\x5B\x32\x34\x3B\x32\x7E"}
};

KeyData::MetaData const &KeyData::Scan(const char* instr)
{
    for(auto const& K : KeyData::KeyDB)
    {
        if(std::string(K.Seq.data()) == instr) return K;
    }
    return NullKey;
}

bool KeyData::IsMeta(const char *instr)
{
    return instr != nullptr && instr[0] == 0x1b;
}

bool KeyData::ESCKey(const char *instr)
{
    return instr != nullptr && instr[0] == 0x1b && (std::strlen((const char*)instr) == 1);
}

KeyData::KeyData(KeyData::MetaData M): M(M), Meta(1),Shift(0),Ctrl(0),Alt(0){}

Book::Action KeyData::KeyInDelegate(std::string_view in)
{
    if(KeyData::ESCKey(in.data()))
    {
        // Real ESC Hit by User. It is a "Cancel/ESC/Abort/..." event.
        KeyData K =  KeyData(in.data());
        // Push K into the EventQeu;
        return Book::Action::End; // Signal End to the Caller (ConIO as of now).
    }
    if(KeyData::IsMeta(in.data()))
    {
        auto M = KeyData::Scan(in.data());
        KeyData K = KeyData(M);
        if (K.M.Enum == KeyData::Null) {
            // not meta
            K.M.Enum = KeyData::Text;
            K.M.Name = "Escaped Meta Input Key Sequence";
            K.Seq = in;
            K.Meta = 1;
        }
        /* push Key in the event queu :*/

    }
    return Book::Action::Continue;
}

KeyData::KeyData(std::string Seq):Seq(std::move(Seq)), Meta(0),Shift(0),Ctrl(0),Alt(0){}

using std::string;

KeyData::~KeyData()
{
    Seq.~string();
}


}