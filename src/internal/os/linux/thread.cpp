/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "thread.h"

namespace Os
{
namespace Linux
{

Thread::Thread(const char* nameP, ThreadFunc funcInitP, ThreadFunc funcP, void* pParamP)
    : nameM{nameP}
    , threadIdM{0}
    , funcInitM{funcInitP}
    , funcM{funcP}
    , paramM{pParamP}
{
}

bool Thread::start()
{
    if (pthread_create(&threadIdM, NULL, &Thread::run, this) == 0)
    {
        barrierM.wait();
        return true;
    }
    return false;
}

void Thread::join()
{   
    pthread_join(threadIdM, NULL);
}

unsigned long int Thread::getId() const
{
#ifdef OS_LINUX
    return threadIdM;
#else
    return 0;
#endif
}

const char* Thread::getName() const
{
    return nameM.c_str();
}

void* Thread::run(void* pParamP)
{
    Thread* pThread = static_cast<Thread*>(pParamP);
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
    return nullptr;
}

} // namespace Linux
} // namespace Os