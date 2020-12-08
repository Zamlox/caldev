/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "thread.h"

namespace Os
{

bool Thread::create(const char* nameP, ThreadFunc funcP, void* pParamP)
{
    return implM.create(nameP, funcP, pParamP);
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