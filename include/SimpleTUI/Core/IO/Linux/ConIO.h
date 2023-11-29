/***************************************************************************
 *   Copyright (C) 1965/1987/2023 by Serge Lussier                         *
 *   serge.lussier@oldlonecoder.club                                       *
 *                                                                         *
 *                                                                         *
 *   Unless otherwise specified, all code in this project is written       *
 *   by the author (Serge Lussier)                                         *
 *   and no one else then not even {copilot, chatgpt, or any other AI}     *
 *   --------------------------------------------------------------------- *
 *   Copyrights from authors other than Serge Lussier also apply here      *
 ***************************************************************************/

#pragma once

#include <unordered_map>
#include <thread>
#include <mutex>

#include <termios.h>
#include <unistd.h>
#include <AppBook/Util/Object.h>
#include <AppBook/Util/Geometry.h>
#include <AppBook/Book/AppBook.h>
#include "IOListener.h"

#include <string_view>

#include "SimpleTUI/Core/IO/Linux/KeyData.h"

/* Pour platforme universelle : */









namespace Tui::IO
{



/*!
 * \brief The ConIO class
 * ...
 */
class STUI_EXPORT ConIO : public Util::Object
{

    Dim WH;
    // ------------- io thread -------------------------
    // delegate/slot:
    std::mutex inmtx{};
    std::thread io_thread;

    Book::Action key_in(ifd& fd);
    Book::Action idle();
    termios raw{};
    termios con{};
    ConIO* _self{};
    listener io_listener{};
    Delegate<> _idle_signal{"oldcc::io idle notifier"};
    Delegate<char*> kbhit_notifier;

public:

private:
    ConIO();
    [[maybe_unused]] explicit ConIO(Object* parent_obj, const std::string& ConId);
public:

    static ConIO& Construct(Object* ParentObj, const std::string& ConID);

    ~ConIO() override = default;
    std::thread& thread_id() { return io_thread;}
    Book::Result Start();
    Book::Result Terminate();
    void operator()(); ///< Callable object as Set as the (std::)thread starter;
    Delegate<>& idle_notifier() { return _idle_signal; }
    Delegate<char*>& kbhit_notify(char* seq) { return kbhit_notifier; }


    static void Clear();
    static void GotoXY(Point Pt={});
    static void Underline(bool On=true);
    static void DoubleUnderline(bool On=true);
    static void RestoreScreen();
    static void SaveScreen();

    static ConIO& Instance();

    static void ToLineEnd();
    static void ToLineStart();



};


}

