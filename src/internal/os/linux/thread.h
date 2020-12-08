/**
 * Author: 		Iosif Haidu
 * Description: IThread implementation for Linux OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_LINUX_THREAD_H__
#define __OS_LINUX_THREAD_H__

#include "ithread.h"
#include "barrier.h"
#include <pthread.h>
#include <string>

namespace Os
{
namespace Linux 
{

/**
 * Linux implementation of IThread interface
 */
class Thread : public IThread
{
public:
    Thread();
    /** see IThread::create() */
    bool create(const char* nameP, ThreadFunc funcP, void* pParamP) override;
    /** see IThread::join() */
    void join() override;
    /** see IThread::getId() */
    unsigned long int getId() const override;
    /** see IThread::getName() */
    const char* getName() const override;

private:
    /**
     * Thread execution function
     * 
     * @param  {void*} pParamP : parameter to pass to thread
     */
    static void* run(void* pParamP);

    /** Thread name */
    std::string nameM;
    /** Thread identification data */
    pthread_t threadIdM;
    /** User function to be executed */
    ThreadFunc funcM;
    /** Parameter to pas to funcM */
    void* paramM;
    /** Used to signal caller that thread started to execute */
    Barrier barrierM;

};

} // namespace Linux
} // namespace Os

#endif // __OS_LINUX_THREAD_H__