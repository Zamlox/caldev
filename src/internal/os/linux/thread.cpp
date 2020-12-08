/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "thread.h"

namespace Os
{
namespace Linux
{

Thread::Thread()
    : nameM{""}
    , threadIdM{0}
    , funcM{nullptr}
    , paramM{nullptr}
{
}

bool Thread::create(const char* nameP, ThreadFunc funcP, void* pParamP)
{
    nameM = nameP;
    funcM = funcP;
    paramM = pParamP;
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
    return threadIdM;
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
        pThread->barrierM.signal();
        pThread->funcM(pThread->paramM);
    }
    return nullptr;
}

} // namespace Linux
} // namespace Os