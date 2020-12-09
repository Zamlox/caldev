/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "thread.h"

namespace Os
{
Thread::Thread(const char* nameP, ThreadFunc funcInitP, ThreadFunc funcP, void* pParamP)
    : implM{nameP, funcInitP, funcP, pParamP}
{
}

bool Thread::start()
{   
    return implM.start();
}

void Thread::join()
{   
    implM.join();
}

unsigned long int Thread::getId() const
{
    return implM.getId();
}

const char* Thread::getName() const
{
    return implM.getName();
}


} // namespace Os