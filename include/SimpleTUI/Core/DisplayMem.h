//
// Created by oldlonecoder on 11/20/23.
//

//#ifndef SIMPLETUI_DISPLAYMEM_H
//#define SIMPLETUI_DISPLAYMEM_H
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

#include "SimpleTUI/Core/StUIDefinitions.h"
#include <AppBook/Util/Geometry.h>
#include <AppBook/Util/Object.h>



namespace Tui
{


using ::Util::Object;

class STUI_EXPORT DisplayMem : public Object
{

protected:
    Dim     Area{0,0,{0,500},{0,500}};
    Point   Location{};      ///< Relative or TopLevel screen coordinates
    Rect    VisibleArea{};

public:
    DisplayMem() = default;
    ~DisplayMem() override;

    DisplayMem(Object* ParentObj,  const std::string& ID);

    struct STUI_EXPORT Char
    {
        using Type = uint32_t;
        Char::Type C{0};

        // ============== Bitmasks =============================
        static constexpr uint32_t CharMask	= 0x000000FF;
        static constexpr uint32_t FGMask	= 0x0000FF00;
        static constexpr uint32_t BGMask	= 0x00FF0000;
        static constexpr uint32_t ColorMask = 0x00FFFF00;
        static constexpr uint32_t AttrMask	= 0xFF000000;
        static constexpr uint32_t UTFMASK	= 0x11000000;
        // ==================Attributes==========================
        static constexpr uint32_t  Glyph 	= 0x01000000;
        static constexpr uint32_t  Underline= 0x02000000;
        static constexpr uint32_t  Stroke 	= 0x04000000;
        static constexpr uint32_t  Blink 	= 0x08000000;
        static constexpr uint32_t  Accent 	= 0x10000000;
        // ==============Bit Shift ============================
        static constexpr int FGShift = 0x08;
        static constexpr int BGShift = 0x10;
        static constexpr int ATShift = 0x18;

        Char() = default;
        ~Char() = default;
        explicit Char(Color::Pair P);
        explicit Char(char c) { C = c;}
        explicit Char(Char::Type V) { C = V;}
        //Char(Color::Pair P) { SetColors(P);}

        Char& operator = (char c);
        Char& operator = (Char R);
        Char& operator = (Char::Type R);

        DisplayMem::Char& SetFG(Color::Code FG);
        DisplayMem::Char& SetBG(Color::Code BG);

        [[maybe_unused]] DisplayMem::Char& SetAttributes(DisplayMem::Char::Type D);


        DisplayMem::Char& SetColors(Color::Pair P);



        Color::Code Fg() const;
        Color::Code Bg() const;

        [[maybe_unused]] Color::Pair Colors();
        Utf::Glyph::Type IconID() const;
        Utf::AccentFR::Type AccentID() const;
        uint8_t Ascii() const;

        DisplayMem::Char::Type& operator*() { return C; }
        DisplayMem::Char::Type Attributes() const;

        DisplayMem::Char& operator << (Utf::Glyph::Type IC);
        DisplayMem::Char& operator << (Utf::AccentFR::Type A);
        DisplayMem::Char& operator << (char c) { C = C & (~CharMask) | c; return *this; }
        std::string Render();
        DisplayMem::Char& ResetAttributes(DisplayMem::Char::Type Bits);
        operator std::string();

        std::string Details();


    };

    virtual Book::Result Resize(Dim DWH);

protected:

    State::Type VisualState{State::Normal};

    virtual Book::Result Render(Rect R);
    virtual Book::Result Allocate(Dim DXY);
    virtual Book::Result Render();
    virtual Book::Result Allocate();

    virtual void AssignColors();

private:
    using DisplayLine = std::vector<DisplayMem::Char>;
    using Display = std::vector<DisplayMem::DisplayLine>;
    DisplayMem::Display Lines;
    ColorDB::Components Colors;
public:

    virtual Book::Result Clear(DisplayMem::Char Ch);
};

} // Tui

//#endif //SIMPLETUI_DISPLAYMEM_H
