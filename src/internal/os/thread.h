/**
 * Author: 		Iosif Haidu
 * Description: Cross platform thread implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_THREAD_H__
#define __OS_THREAD_H__

#include "internal/os/ithread.h"
#ifdef OS_WINDOWS
#include "internal/os/windows/thread.h"
#else
#include "internal/os/linux/thread.h"
#endif

namespace Os 
{
/**
 * Creoss platform implementation for IThread
 */
class Thread : public IThread
{
public:
    /**
     * Initialize thread data.
     * 
     * @param  {char*} nameP          : thread name
     * @param  {ThreadFunc} funcInitP : function to be executed in thread before signaling caller
     * @param  {ThreadFunc} funcP     : function to be executed in thread after signaling caller
     * @param  {void*} pParamP        : parameter to be passed to funcInitP and funcP
     */
    Thread(const char* nameP, ThreadFunc funcInitP, ThreadFunc funcP, void* pParamP);
    /** see IThread::start() */
    bool start() override;
    /** see IThread::join() */
    void join() override;
    /** see IThread::getId() */
    unsigned long int getId() const override;
    /** see IThread::getName() */
    const char* getName() const override;

private:
#ifdef OS_WINDOWS
    Os::Windows::Thread implM;
#else
    Os::Linux::Thread implM;
#endif
};

} // namespace Os

#endif // __OS_THREAD_H__