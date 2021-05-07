/**
 * Author: 		Iosif Haidu
 * Description: Guarding lock for mutexes
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/mutex.h"

namespace Os
{

/**
 * Lock guard for mutex.
 */
class lock_guard
{
public:
    lock_guard(Mutex& rMutexP)
        : rMutexM{rMutexP}
    {
        rMutexM.lock();
    }
    ~lock_guard()
    {
        rMutexM.unlock();
    }

private:
    Mutex& rMutexM;
};

} // namespace Os