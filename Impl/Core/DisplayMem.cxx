//
// Created by oldlonecoder on 11/20/23.
//

#include "SimpleTUI/Core/DisplayMem.h"

namespace Tui
{

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
const std::map<std::string, TileEncoding> tile_encoding = { // NOLINT
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




Book::Result DisplayMem::Allocate(Dim DXY)
{
    Lines.clear();
    Lines.resize(DXY.H);
    auto ECP = Colors[State::Normal];
    Char Ch = ECP;
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

DisplayMem::DisplayMem(Object *ParentObj, const std::string &ID) : Object(ParentObj, ID){}




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
    Render();
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
    }

    return Book::Result::Ok;
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

DisplayMem::Char &DisplayMem::Char::SetAttributes(DisplayMem::Char::Type D)
{
    C = (C & ~AttrMask) | D;
    return *this;
}


DisplayMem::Char &DisplayMem::Char::SetColors(Color::Pair P)
{
    return SetFG(P.Fg).SetBG(P.Bg);
}

Color::Code DisplayMem::Char::Fg()
{
    return static_cast<Color::Code>(C & ~FGMask >> FGShift);
}

Color::Code DisplayMem::Char::Bg()
{
    return static_cast<Color::Code>(C & ~BGMask >> BGShift);
}

Color::Pair DisplayMem::Char::Colors()
{
    return Color::Pair{Fg(), Bg()};
}

Utf::Glyph::Type DisplayMem::Char::IconID()
{
    return static_cast<Utf::Glyph::Type>(C & CharMask);
}

Utf::AccentFR::Type DisplayMem::Char::AccentID()
{
    return static_cast<Utf::AccentFR::Type>(C & CharMask);

}

uint8_t DisplayMem::Char::Ascii()
{
    return C & CharMask;
}

DisplayMem::Char::Type DisplayMem::Char::Attributes()
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