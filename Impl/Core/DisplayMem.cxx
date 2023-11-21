//
// Created by oldlonecoder on 11/20/23.
//

#include "SimpleTUI/Core/DisplayMem.h"

namespace Tui
{


#pragma region TileEncoding
// -------------------------------------------------------------------------------------------
// Copyright 2022 Arthur Sonzogni. All rights reserved.
// Use of this source code is governed by the MIT license
struct TileEncoding {
    uint8_t left : 2;
    uint8_t top : 2;
    uint8_t right : 2;
    uint8_t down : 2;
    uint8_t round : 1;

    // clang-format off
    bool operator<(const TileEncoding& other) const {
        if (left < other.left)   { return  true;  }
        if (left > other.left)   { return  false; }
        if (top < other.top)     { return  true;  }
        if (top > other.top)     { return  false; }
        if (right < other.right) { return  true;  }
        if (right > other.right) { return  false; }
        if (down < other.down)   { return  true;  }
        if (down > other.down)   { return  false; }
        if (round < other.round) { return  true;  }
        if (round > other.round) { return  false; }
        return false;
    }
    // clang-format on
};

// clang-format off
const std::map<std::string, TileEncoding> tile_encoding =
    { // NOLINT
    {"─", {1, 0, 1, 0, 0}},
    {"━", {2, 0, 2, 0, 0}},
    {"╍", {2, 0, 2, 0, 0}},

    {"│", {0, 1, 0, 1, 0}},
    {"┃", {0, 2, 0, 2, 0}},
    {"╏", {0, 2, 0, 2, 0}},

    {"┌", {0, 0, 1, 1, 0}},
    {"┍", {0, 0, 2, 1, 0}},
    {"┎", {0, 0, 1, 2, 0}},
    {"┏", {0, 0, 2, 2, 0}},

    {"┐", {1, 0, 0, 1, 0}},
    {"┑", {2, 0, 0, 1, 0}},
    {"┒", {1, 0, 0, 2, 0}},
    {"┓", {2, 0, 0, 2, 0}},

    {"└", {0, 1, 1, 0, 0}},
    {"┕", {0, 1, 2, 0, 0}},
    {"┖", {0, 2, 1, 0, 0}},
    {"┗", {0, 2, 2, 0, 0}},

    {"┘", {1, 1, 0, 0, 0}},
    {"┙", {2, 1, 0, 0, 0}},
    {"┚", {1, 2, 0, 0, 0}},
    {"┛", {2, 2, 0, 0, 0}},

    {"├", {0, 1, 1, 1, 0}},
    {"┝", {0, 1, 2, 1, 0}},
    {"┞", {0, 2, 1, 1, 0}},
    {"┟", {0, 1, 1, 2, 0}},
    {"┠", {0, 2, 1, 2, 0}},
    {"┡", {0, 2, 2, 1, 0}},
    {"┢", {0, 1, 2, 2, 0}},
    {"┣", {0, 2, 2, 2, 0}},

    {"┤", {1, 1, 0, 1, 0}},
    {"┥", {2, 1, 0, 1, 0}},
    {"┦", {1, 2, 0, 1, 0}},
    {"┧", {1, 1, 0, 2, 0}},
    {"┨", {1, 2, 0, 2, 0}},
    {"┩", {2, 2, 0, 1, 0}},
    {"┪", {2, 1, 0, 2, 0}},
    {"┫", {2, 2, 0, 2, 0}},

    {"┬", {1, 0, 1, 1, 0}},
    {"┭", {2, 0, 1, 1, 0}},
    {"┮", {1, 0, 2, 1, 0}},
    {"┯", {2, 0, 2, 1, 0}},
    {"┰", {1, 0, 1, 2, 0}},
    {"┱", {2, 0, 1, 2, 0}},
    {"┲", {1, 0, 2, 2, 0}},
    {"┳", {2, 0, 2, 2, 0}},

    {"┴", {1, 1, 1, 0, 0}},
    {"┵", {2, 1, 1, 0, 0}},
    {"┶", {1, 1, 2, 0, 0}},
    {"┷", {2, 1, 2, 0, 0}},
    {"┸", {1, 2, 1, 0, 0}},
    {"┹", {2, 2, 1, 0, 0}},
    {"┺", {1, 2, 2, 0, 0}},
    {"┻", {2, 2, 2, 0, 0}},

    {"┼", {1, 1, 1, 1, 0}},
    {"┽", {2, 1, 1, 1, 0}},
    {"┾", {1, 1, 2, 1, 0}},
    {"┿", {2, 1, 2, 1, 0}},
    {"╀", {1, 2, 1, 1, 0}},
    {"╁", {1, 1, 1, 2, 0}},
    {"╂", {1, 2, 1, 2, 0}},
    {"╃", {2, 2, 1, 1, 0}},
    {"╄", {1, 2, 2, 1, 0}},
    {"╅", {2, 1, 1, 2, 0}},
    {"╆", {1, 1, 2, 2, 0}},
    {"╇", {2, 2, 2, 1, 0}},
    {"╈", {2, 1, 2, 2, 0}},
    {"╉", {2, 2, 1, 2, 0}},
    {"╊", {1, 2, 2, 2, 0}},
    {"╋", {2, 2, 2, 2, 0}},

    {"═", {3, 0, 3, 0, 0}},
    {"║", {0, 3, 0, 3, 0}},

    {"╒", {0, 0, 3, 1, 0}},
    {"╓", {0, 0, 1, 3, 0}},
    {"╔", {0, 0, 3, 3, 0}},

    {"╕", {3, 0, 0, 1, 0}},
    {"╖", {1, 0, 0, 3, 0}},
    {"╗", {3, 0, 0, 3, 0}},

    {"╘", {0, 1, 3, 0, 0}},
    {"╙", {0, 3, 1, 0, 0}},
    {"╚", {0, 3, 3, 0, 0}},

    {"╛", {3, 1, 0, 0, 0}},
    {"╜", {1, 3, 0, 0, 0}},
    {"╝", {3, 3, 0, 0, 0}},

    {"╞", {0, 1, 3, 1, 0}},
    {"╟", {0, 3, 1, 3, 0}},
    {"╠", {0, 3, 3, 3, 0}},

    {"╡", {3, 1, 0, 1, 0}},
    {"╢", {1, 3, 0, 3, 0}},
    {"╣", {3, 3, 0, 3, 0}},

    {"╤", {3, 0, 3, 1, 0}},
    {"╥", {1, 0, 1, 3, 0}},
    {"╦", {3, 0, 3, 3, 0}},

    {"╧", {3, 1, 3, 0, 0}},
    {"╨", {1, 3, 1, 0, 0}},
    {"╩", {3, 3, 3, 0, 0}},

    {"╪", {3, 1, 3, 1, 0}},
    {"╫", {1, 3, 1, 3, 0}},
    {"╬", {3, 3, 3, 3, 0}},

    {"╭", {0, 0, 1, 1, 1}},
    {"╮", {1, 0, 0, 1, 1}},
    {"╯", {1, 1, 0, 0, 1}},
    {"╰", {0, 1, 1, 0, 1}},

    {"╴", {1, 0, 0, 0, 0}},
    {"╵", {0, 1, 0, 0, 0}},
    {"╶", {0, 0, 1, 0, 0}},
    {"╷", {0, 0, 0, 1, 0}},

    {"╸", {2, 0, 0, 0, 0}},
    {"╹", {0, 2, 0, 0, 0}},
    {"╺", {0, 0, 2, 0, 0}},
    {"╻", {0, 0, 0, 2, 0}},

    {"╼", {1, 0, 2, 0, 0}},
    {"╽", {0, 1, 0, 2, 0}},
    {"╾", {2, 0, 1, 0, 0}},
    {"╿", {0, 2, 0, 1, 0}},
};
// clang-format on

// -------------------------------------------------------------------------------------------------------------------

#pragma endregion TileEncoding


Book::Result DisplayMem::Allocate(Dim DXY)
{
    Lines.clear();
    Lines.resize(DXY.H);
    Color::Pair  ECP = Colors[State::Normal];
    Char Ch{ECP};
    Ch << (char)0x20;
    for(auto& L : Lines)
    {
        L.resize(DXY.W);

        std::fill(L.begin(), L.end(), Ch);
    }

    return Book::Result::Ok;
}

DisplayMem::~DisplayMem()
{
    Lines.clear();
}

DisplayMem::DisplayMem(Object *ParentObj, const std::string &ID) : Object(ParentObj, ID)
{
    Colors = ColorDB::ColorDBData["default"]["ControlBase"];

}




/*!
 * @brief
 * @param DWH
 * @return
 * @note Will Reallocate non-destructively...And Re-Origanize the children Display
 */
Book::Result DisplayMem::Resize(Dim DWH)
{
    //...
    Allocate(DWH);
    return Render();
}


/*!
 * @brief Renders at the screen
 * @return
 * @note Compute/Update the Visible Area within the exposed subregion
 */
Book::Result DisplayMem::Render(Rect R)
{
    if(!R)
    {
        // Render All mem.
        //...
        return Book::Result::Accepted;
    }

    Rect A = Rect{{0,0}, Area} & R;
    if(!A)
        return Book::Result::Rejected;


    return Book::Result::Ok;
}

Book::Result DisplayMem::Render()
{
    return Book::Result::Ok;
}

Book::Result DisplayMem::Allocate()
{

    if(!Area)
        throw AppBook::Exception()[ AppBook::Fatal() << " Attempt to 'Allocate' Display Memory Bloc with unset dimensions"];

    Lines.clear();
    Lines.resize(Area.H);
    Color::Pair  ECP = Colors[State::Normal];
    Char Ch{ECP};
    Ch << (char)0x20;
    for(auto& L : Lines)
    {
        L.resize(Area.W,Ch);
        //std::fill(L.begin(), L.end(), Ch);
    }
    return Book::Result::Accepted;
}

Book::Result DisplayMem::Clear(DisplayMem::Char Ch)
{
    if(Lines.empty())
        return Book::Result::Rejected;

    for(auto& L:Lines)
    {
        std::fill(L.begin(), L.end(), Ch);
    }
    return Book::Result::Accepted;
}

void DisplayMem::AssignColors()
{
    Colors = ColorDB::ColorDBData["default"]["ControlBase"];
}


DisplayMem::Char &DisplayMem::Char::operator=(char c)
{
    C = (C & ~CharMask) | c;
    return *this;
}

DisplayMem::Char &DisplayMem::Char::operator=(DisplayMem::Char R)
{
    C = R.C;
    return *this;
}

DisplayMem::Char &DisplayMem::Char::operator=(DisplayMem::Char::Type R)
{
    C = R;
    return *this;
}

DisplayMem::Char &DisplayMem::Char::SetFG(Color::Code FG)
{
    C = (C & ~FGMask) | FG << FGShift;
    return *this;
}

DisplayMem::Char &DisplayMem::Char::SetBG(Color::Code BG)
{
    C = (C & ~BGMask) | BG << BGShift;
    return *this;
}

[[maybe_unused]] DisplayMem::Char &DisplayMem::Char::SetAttributes(DisplayMem::Char::Type D)
{
    C = (C & ~AttrMask) | D;
    return *this;
}


DisplayMem::Char &DisplayMem::Char::SetColors(Color::Pair P)
{
    return SetFG(P.Fg).SetBG(P.Bg);
}

Color::Code DisplayMem::Char::Fg() const
{
    return static_cast<Color::Code>(C & ~FGMask >> FGShift);
}

Color::Code DisplayMem::Char::Bg() const
{
    return static_cast<Color::Code>(C & ~BGMask >> BGShift);
}

[[maybe_unused]] Color::Pair DisplayMem::Char::Colors()
{
    return Color::Pair{Fg(), Bg()};
}

Utf::Glyph::Type DisplayMem::Char::IconID() const
{
    return static_cast<Utf::Glyph::Type>(C & CharMask);
}

Utf::AccentFR::Type DisplayMem::Char::AccentID() const
{
    return static_cast<Utf::AccentFR::Type>(C & CharMask);

}

char DisplayMem::Char::Ascii() const
{
    return C & CharMask;
}

DisplayMem::Char::Type DisplayMem::Char::Attributes() const
{
    return C & AttrMask;
}

DisplayMem::Char &DisplayMem::Char::operator<<(Utf::Glyph::Type IC)
{
    C = (C & ~(UTFMASK | CharMask)) | Glyph | IC;
    return *this;
}

DisplayMem::Char &DisplayMem::Char::operator<<(Utf::AccentFR::Type A)
{
    C = (C & ~(UTFMASK | CharMask)) | Accent | A;
    return *this;
}

std::string DisplayMem::Char::Render()
{
    return " ";
}

DisplayMem::Char &DisplayMem::Char::ResetAttributes(DisplayMem::Char::Type Bits)
{
    C = (C & ~Char::AttrMask) | Bits;
    return *this;
}

DisplayMem::Char::operator std::string()
{
    return " ";
}

std::string DisplayMem::Char::Details()
{
    return " ";
}

DisplayMem::Char::Char(Color::Pair P)
{
    SetFG(P.Fg);
    SetBG(P.Bg);
}


} // Tui