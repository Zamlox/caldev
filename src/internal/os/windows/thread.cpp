/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "thread.h"
#include "processthreadsapi.h"

namespace Os
{
namespace Windows
{

Thread::Thread(const char* nameP, ThreadFunc funcInitP, ThreadFunc funcP, void* pParamP)
    : nameM{nameP}
    , threadHandleM{NULL}
    , threadIdM{0}
    , funcInitM{funcInitP}
    , funcM{funcP}
    , paramM{pParamP}
{
}

bool Thread::start()
{
    if ((threadHandleM = CreateThread(NULL, 0, run, this, 0, &threadIdM)) != NULL)
    {
        barrierM.wait();
        return true;
    }
    return false;
}

void Thread::join()
{   
    WaitForSingleObject(threadHandleM, INFINITE);
}

unsigned long int Thread::getId() const
{
    return threadIdM;
}

const char* Thread::getName() const
{
    return nameM.c_str();
}

DWORD WINAPI Thread::run( LPVOID lpParam )
{
    Thread* pThread = static_cast<Thread*>(lpParam);
    if (pThread)
    {
        if (pThread->funcInitM)
        {
            pThread->funcInitM(pThread->paramM);
        }
        pThread->barrierM.signal();
        if (pThread->funcM)
        {
            pThread->funcM(pThread->paramM);
        }
    }
    return 0;
}

} // namespace Windows
} // namespace Os