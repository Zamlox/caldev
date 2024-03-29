/**
 * Author:      Iosif Haidu
 * Description: IMutex implementation for Linux OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/imutex.h"
#include <pthread.h>

namespace Os
{
namespace Linux
{

/**
 * Mutex implementation
 */
class Mutex : public IMutex
{
public:
    Mutex();
    ~Mutex();
    void lock() override;
    void unlock() override;

private:
    pthread_mutexattr_t mutexAttrM;
    pthread_mutex_t mutexM;
};

} // namespace Linux
} // namespace Os
