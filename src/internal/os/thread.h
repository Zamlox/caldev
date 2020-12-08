/**
 * Author: 		Iosif Haidu
 * Description: Cross platform thread implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_THREAD_H__
#define __OS_THREAD_H__

#include "ithread.h"
#ifdef OS_LINUX
#include "linux/thread.h"
#endif

namespace Os 
{
/**
 * Creoss platform implementation for IThread
 */
class Thread : public IThread
{
public:
    /** see IThread::create() */
    bool create(const char* nameP, ThreadFunc funcInitP, ThreadFunc funcP, void* pParamP) override;
    /** see IThread::join() */
    void join() override;
    /** see IThread::getId() */
    unsigned long int getId() const override;
    /** see IThread::getName() */
    const char* getName() const override;

private:
#ifdef OS_LINUX
    Os::Linux::Thread implM;
#endif
};

} // namespace Os

#endif // __OS_THREAD_H__