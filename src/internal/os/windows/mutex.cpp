/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/os/windows/mutex.h"

namespace Os
{
namespace Windows
{

Mutex::Mutex()
{
    InitializeCriticalSection(&mutexM);
}

Mutex::~Mutex()
{
    DeleteCriticalSection(&mutexM);
}

void Mutex::lock()
{
    EnterCriticalSection(&mutexM);
}

void Mutex::unlock()
{
    LeaveCriticalSection(&mutexM);
}

} // namespace Windows
} // namespace Os
