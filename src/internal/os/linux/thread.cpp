/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/os/linux/thread.h"

namespace Os
{
namespace Linux
{

unsigned long int Thread::threadIdS{0};

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
        threadIdS++;
        mapPThreadT2IntM.insert(std::make_pair(threadIdM, threadIdS));
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
    if (ThreadIdMap::const_iterator it = mapPThreadT2IntM.find(threadIdM); it != mapPThreadT2IntM.end())
    {
        return it->second;
    }
    return 0;
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