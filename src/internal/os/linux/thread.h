/**
 * Author: 		Iosif Haidu
 * Description: IThread implementation for Linux OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/ithread.h"
#include "internal/os/linux/barrier.h"
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
    /** User function to be executed before signaling caller */
    ThreadFunc funcInitM;
    /** User function to be executed after signaling caller */
    ThreadFunc funcM;
    /** Parameter to pas to funcM */
    void* paramM;
    /** Used to signal caller that thread started to execute */
    Barrier barrierM;
};

} // namespace Linux
} // namespace Os
