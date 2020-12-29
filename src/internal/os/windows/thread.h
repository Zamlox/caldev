/**
 * Author: 		Iosif Haidu
 * Description: IThread implementation for Windows OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_WINDOWS_THREAD_H__
#define __OS_WINDOWS_THREAD_H__

#include "internal/os/ithread.h"
#include "internal/os/windows/barrier.h"
#include <windows.h>
#include <string>

namespace Os
{
namespace Windows 
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
     * @param  {LPVOID} lpParam : parameter to pass to thread
     * @return {DWORD}          : 0 if success
     */
    static DWORD WINAPI run( LPVOID lpParam );

    /** Thread name */
    std::string nameM;
    /** Thread handle */
    HANDLE threadHandleM;
    /** Thread id */
    DWORD threadIdM;
    /** User function to be executed before signaling caller */
    ThreadFunc funcInitM;
    /** User function to be executed after signaling caller */
    ThreadFunc funcM;
    /** Parameter to pas to funcM */
    void* paramM;
    /** Used to signal caller that thread started to execute */
    Barrier barrierM;

};

} // namespace Windows
} // namespace Os

#endif // __OS_WINDOWS_THREAD_H__