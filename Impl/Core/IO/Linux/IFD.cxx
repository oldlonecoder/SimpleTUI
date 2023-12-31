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


#include "SimpleTUI/Core/IO/Linux/IFD.h"
#include <sys/ioctl.h>
#include <string>



namespace Tui::IO
{


ifd::ifd():
    fd(0), options(0), pksize(0), wsize(0), wpos(0), internal_buffer(0)
{

}

ifd::ifd(int fd_, uint32_t opt_):
    fd(fd_), options(opt_), pksize(0), wsize(0), wpos(0), internal_buffer(0)
{

}

ifd::~ifd()
{
    read_signal.DisconnectAll();
    write_signal.DisconnectAll();
    idle_signal.DisconnectAll();

    if(options & O_XBUF) return;
    delete [] internal_buffer;
}

std::size_t ifd::toread()
{
    ioctl(fd,FIONREAD,&pksize);
    return pksize;
}

ifd::ifd(ifd &&f) noexcept
{
    internal_buffer = f.internal_buffer;
    options = f.options;
    state = f.state;
    fd = f.fd;
    read_signal = std::move(f.read_signal);
    write_signal = std::move(f.write_signal);
    idle_signal = std::move(f.idle_signal);

}


ifd &ifd::operator=(ifd && f) noexcept {
    internal_buffer = f.internal_buffer;
    options = f.options;
    state = f.state;
    fd = f.fd;
    read_signal = std::move(f.read_signal);
    write_signal = std::move(f.write_signal);
    idle_signal = std::move(f.idle_signal);
    return *this;
}

/*!
 * @brief [en]: defines the next window-size of datablock to receive
       [frang]: Definir la window-size du prochain bloc de donnees a recevoir
 * @param sz u_int32_t size
 * @return sz
 * @author &copy; 2011, Serge Lussier (bretzel)
 * @note [frang]: On doit s'assurer que le nombre de bytes attendus soit effectivement ce que la session distante nous envoie.
 *          [en]: Make sure that the number of bytes to be received must be of the same size on the remote session.
 */
std::size_t ifd::set_window_size(uint32_t sz)
{
    if (internal_buffer)
        delete [] internal_buffer;
    options |= O_BUF|O_WINDOWED;
    wpos = 0;
    wsize  = sz;
    internal_buffer = new u_int8_t[sz + 4];
    std::memset(internal_buffer, 0, sz);
    return wsize;
}

Book::Action ifd::data_in()
{
    (void)toread();
    if (pksize <=0) {
        // Any value under 1 mean there is error or hangup on file descriptor held by this ifd. So it is systematic shutdown using
        // zero_signal notify.
        AppBook::Status() << " shutdown signal on  file descriptor #" << fd << " : ";
        return zero_signal(*this);
    }
    if(pksize > max_pksize )
    {
        AppBook::Status() << Book::Result::Overflow << " packet size:" << Color::Yellow << pksize
                                 << Color::Reset << " max set to " <<  Color::Yellow << max_pksize
                                 << Color::Reset << " ignoring.";
        return Book::Action::End;
    }

    if(options & I_AUTOFILL)
    {
        if(!internal_buffer) internal_buffer = new uint8_t[4 * 1024]; // < Arbitrary buffer ....
        std::memset(internal_buffer, 0, 4 * 1024);
        (void) ::read(fd, internal_buffer, pksize);
        return read_signal(*this);
    }
    //log_debugfn << m_pksize << " bytes to read:" << log_end;
    auto*  tbuf= new uint8_t[pksize+5];
    if (options & (O_WINDOWED)) {
        AppBook::Debug() << " this ifd has (WINDOWED) options :" << Book::Fn::Endl << "     size of window:" << wsize;
        uint32_t waitingsz = wsize-wpos;
        uint32_t rsz;
        if (pksize > waitingsz ) waitingsz = wsize-pksize;
        rsz = read(fd, tbuf, pksize); // We read ALL waiting bytes, overflow will be discarded!
        if ( rsz > waitingsz) rsz -= rsz-wsize;
        memcpy(internal_buffer + wpos, tbuf, rsz); // overflow discarded here. ( pourrais invalider le datablock dans le protocol... tant-pis!)
        wpos += rsz;
        if (wpos >= wsize)
        {
            // signal to delegate that the window datablock is filled and ready!
            auto R = window_complete_signal(*this);
            if(R != Book::Action::Continue) return R;
            return R;
        }
        // else return remaining bytes to wait for
        return Book::Action::Continue;
    }
    // signal to delegate that data is ready to be pulled from the file descriptor.
    return read_signal(*this);
}

uint32_t ifd::set_options(u_int32_t opt)
{
    options = opt;
    return options;
}


/*!
 * @brief Utility function to write an array of bytes to the fd
 * @param datablock  the array of bytes (u_int8_t)
 * @param sz size of the block
 * @param wait_completed flag to set this function to block on the write until all block content is written or on error
 * @return number of bytes written
 * @author &copy; 2011, Serge Lussier (bretzel)
 * @note
 */
std::size_t ifd::out(uint8_t *datablock, std::size_t sz, bool wait_completed) const
{
    auto _still = sz;
    auto w = _still;
    w = 0;
    uint8_t* pos = datablock;
    if (!wait_completed)
        if(!(options & O_BLOCK))
            return ::write(fd, pos, _still);

    while (_still) {
        w = ::write(fd, pos, _still);
        _still -= w;
        pos += w;
        if (!w)
        {
            AppBook::Error() << " ::write returned 0 bytes written...";
            return 0;
        }
    }
    return _still;
}



Book::Result ifd::clear()
{
    if (internal_buffer)delete [] internal_buffer;
    wpos = wsize = pksize = 0;
    internal_buffer = 0;
    return Book::Result::Ok;
}


}
