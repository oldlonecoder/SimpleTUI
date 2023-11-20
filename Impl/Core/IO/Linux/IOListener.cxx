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


#include "SimpleTUI/Core/IO/Linux/IOListener.h"
#include <sys/socket.h>
#include <errno.h>
#include <error.h>


namespace Tui::IO
{


using Util::Object;

listener::listener(Object *parent_, int msec_) : Object(parent_, "listener"), msec(msec_)
{
    init();
}

listener::~listener()
{
    //shutdown();
    _idle_signal .DisconnectAll();
    _hup_signal  .DisconnectAll();
    _zero_signal .DisconnectAll();
    _error_signal.DisconnectAll();

    _ifds.clear();
}

Book::Result listener::run()
{

    //StrAcc Bin = "%08b";
    //Bin << _epoll_event.events;
    AppBook::Debug() << " _epoll_event.events:" << Color::Yellow << "%08b" << _epoll_event.events << Color::Reset << ":";
    if(!_epoll_event.events)
    {
        AppBook::Info() << "events poll empty - dismissing this listener";
        return Book::Result::Empty;
    }

    auto num = _ifds.size();
    epoll_event events[_maxifd];
    int ev_count=0;

    ifd::iterator i;

    do{
        //AppBook::debug(HERE) << " epoll_wait:";
        ev_count = epoll_wait(_epollfd,events,num,msec);
        //AppBook::debug(HERE) << " epoll_wait:[" << color::Yellow << ev_count << color::Reset << "]:";

        if(!ev_count)
        {
            //AppBook::debug(HERE) << "Invoke _idle_signal(): " << color::Yellow << (_idle_signal.empty() ? "no hook..." : "");
            _idle_signal();
            continue;
        }

        for(int e=0; e < ev_count; e++)
        {
            uint32_t ev = events[e].events;
            int fd = events[e].data.fd;
            //AppBook::info(HERE) << rem::stamp <<  " event on fd " << color::Red4 << fd << color::Reset;
            auto i = query_fd(fd);
            if(i==_ifds.end())
            {
                AppBook::Error() << " event triggered on descriptor which is not in this listener...";
                break;
            }
            Book::Action R{Book::Action::End};
            if(ev & (EPOLLERR | EPOLLHUP))
            {
                err_hup(*i);
                continue;
            }
            if(ev & EPOLLOUT) {
                R = epoll_data_out(*i);
                ///@todo handle R;
                continue;
            }
            if (ev & EPOLLIN) {
                R = epoll_data_in(*i);
                if(R != Book::Action::Continue)
                    AppBook::Status() << " epoll_data_in(" << Color::Yellow << i->fd << Color::Reset << ") breaks.";
                if(R == Book::Action::End) shutdown();
                ///@todo handle R;
                continue;
            }
        }// epoll events iteration
    }while(!_terminate);
    AppBook::Info() << Color::PaleVioletRed1 << " exited from the main loop of the listener: ";
    return Book::Result::Ok;
}




Book::Result listener::add_ifd(int fd_, uint32_t opt_)
{
    AppBook::Debug() << " fd = " << Color::Yellow << fd_;
    auto i = query_fd(fd_);
    if(i != _ifds.end())
    {
        AppBook::Error() << " file descriptor" << fd_ << " already in the epoll set ";
        return Book::Result ::Rejected;
    }

    _ifds.emplace_back(fd_, opt_);

    epoll_event ev{};
    ev.events = _epoll_event.events;
    auto &fd = _ifds.back();
    fd.state.active = true;
    ev.data.fd = fd.fd;
    epoll_ctl(_epollfd, EPOLL_CTL_ADD, fd.fd, &ev );
    AppBook::Info() << " added ifd[fd=" << fd.fd << "]";
    return Book::Result::Accepted;
}

Book::Result listener::remove_ifd(int fd_)
{
    auto i = query_fd(fd_);
    if(i==_ifds.end())
    {
        AppBook::Error() << " fd " << fd_ << " not in this epoll set";
        return Book::Result::Rejected;
    }


    AppBook::Info() << " removing ifd from the epoll set" << Book::Fn::Endl << " fd:" << i->fd;

    auto fdi = i->fd;
    epoll_event ev{};// prend pas de chance pour EPOLL_CTL_DEL - selon la doc, ev doit etre non-null dans la version 2.6.9- du kernel....
    // completement ignor&eacute; dans 2.6.9+
    ev.events = _epoll_event.events;
    ev.data.fd = i->fd;
    epoll_ctl(_epollfd, EPOLL_CTL_DEL, i->fd, &ev );
    _ifds.erase(i);
    AppBook::Info() << " removed fd[" << fdi << "] from the epoll set, and destroyed.";
    return Book::Result::Accepted;
}

Book::Result listener::pause_ifd(int fd_)
{
    auto i = query_fd(fd_);
    if(i==_ifds.end())
    {
        AppBook::Error() << " fd " << fd_ << " not in this epoll set";
        return Book::Result::Rejected;
    }
    epoll_event ev{};// prend pas de chance pour EPOLL_CTL_DEL - selon la doc, ev doit etre non-null dans la version 2.6.9- du kernel....
    // completement ignor&eacute; dans 2.6.9+
    ev.events = _epoll_event.events;
    ev.data.fd = i->fd;
    epoll_ctl(_epollfd, EPOLL_CTL_DEL, i->fd, &ev );
    AppBook::Info() << " fd[" << fd_ <<"] is paused";
    return Book::Result::Accepted;
}

Book::Result listener::init()
{
    AppBook::Debug() << ":";
    _terminate = false;
    _epollfd = epoll_create(_maxifd);
    _epoll_event.events = EPOLLIN | EPOLLPRI | EPOLLERR | EPOLLHUP;
    return Book::Result::Accepted;
}


Book::Result listener::shutdown()
{
    _terminate = true;
    //close/shutdown all ifd's
    for(auto &f : _ifds)
    {
        if(f.fd > 2) // NEVER-EVER shutdown STDIN, STDOUT, or STDERR !!! LOL
            ::shutdown(f.fd, SHUT_RDWR);
    }
    close(_epollfd);
    return Book::Result::Accepted;
}

ifd::iterator listener::query_fd(int fd_)
{
    for(auto it = _ifds.begin(); it != _ifds.end(); it++)
        if(it->fd == fd_) return it;
    return _ifds.end();
}



Book::Result listener::start() {
//    if(_epollfd >=0 ){
//        AppBook::warning(HERE) << "this listener has already been initialized and is probably running as of now! - review this listener management!";
//        return false;
//    }
    return this->run();
}

Book::Action listener::epoll_data_in(ifd &i)
{
    //log_debugfn << log_end;
    i.state.readable = true;
    i.state.writeable = false;
    Book::Action E;
    if(i.state.active){
        //AppBook::debug(HERE) << " reading on fd " << i.fd;
        E = i.data_in();
        if(E != Book::Action::Continue) {
            AppBook::Status() << " rejected expect from the ifd[" << i.fd << "]; - returning;";
            return E;
        }
    }

    // re-enable listening:
    epoll_event e{};
    e.data.fd = i.fd;
    e.events = (i.options & ifd::O_READ) ? EPOLLIN: 0 | (i.options & ifd::O_WRITE) ? EPOLLOUT: 0 |EPOLLERR | EPOLLHUP;
    epoll_ctl(_epollfd, EPOLL_CTL_MOD, i.fd,&e);
    return E;
}

Book::Action listener::epoll_data_out(ifd &i)
{
    if(!(i.options & ifd::O_WRITE))
        return Book::Action::End;

    i.state.readable = false;
    i.state.writeable = true;
    Book::Action E;
    if(i.state.active){
        //AppBook::debug(HERE) << " writting on fd " << i.fd;
        E = i.write_signal(i);
    }
    epoll_event e{};
    e.data.fd = i.fd;
    e.events = (i.options & ifd::O_READ) ? EPOLLIN: 0 | (i.options & ifd::O_WRITE) ? EPOLLOUT: 0 |EPOLLERR | EPOLLHUP;
    epoll_ctl(_epollfd, EPOLL_CTL_MOD, i.fd,&e);
    return E;
}

void listener::err_hup(ifd &f)
{
    AppBook::Error() << Color::White << " fd[" << Color::Yellow << f.fd << Color::White << "] error or hangup - removing file descriptor";
    remove_ifd(f.fd);
}


}

