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

#include "SimpleTUI/Core/IO/Linux/IFD.h"
#include <AppBook/Util/Object.h>
#include <AppBook/Util/Delegate.h>

#include <unistd.h>
#include <cstdio>
#include <cstdlib>
#include <cerrno>
#include <cstring>
#include <sys/types.h>

#include <sys/epoll.h>

#include <fcntl.h>
#include <thread>
#include <mutex>



namespace Tui::IO
{

using Util::Object;

class STUI_EXPORT listener :public Object
{

    ifd::list   _ifds;
    int         _maxifd = 3;
    epoll_event _epoll_event;
    int         _epollfd = -1;
    int         _epollnumfd = -1;
    bool        _terminate = false;
    Delegate<> _idle_signal{"idle"};
    Delegate<ifd&> _hup_signal{"hup"}, _error_signal{"error"}, _zero_signal{"zero"};


    int msec = -1; ///< default to infinite.
public:
    listener()  = default;
    explicit listener(Object* parent_, int msec_=-1);
    ~listener() override;

    Book::Result run();
    Book::Result add_ifd(int fd_, uint32_t opt_);
    Book::Result remove_ifd(int fd_);
    Book::Result pause_ifd(int fd_);
    Book::Result init();
    Book::Result shutdown();
    Delegate<>& idle_signal() { return _idle_signal; }
    Delegate<ifd&>& hup_signal() { return _hup_signal; }
    Delegate<ifd&>& error_signal() { return _error_signal; }
    Delegate<ifd&>& zero_signal() { return _zero_signal; }
    ifd::iterator query_fd(int fd_);
    Book::Result start();
    void err_hup(ifd& f);
    Book::Action epoll_data_in(ifd& i);
    Book::Action epoll_data_out(ifd& i);


private:

};

}

