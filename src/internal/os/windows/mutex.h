/**
 * Author: 		Iosif Haidu
 * Description: IMutex implementation for Windows OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/imutex.h"
#include <windows.h>
#include <synchapi.h>

namespace Os
{
namespace Windows
{

/**
 * Mutex implementation
 */
class Mutex : public IMutex
{
public:
    Mutex();
    ~Mutex();
    /** see IMutex::lock() */
    void lock() override;
    /** see IMutex::unlock() */
    void unlock() override;

private:
    CRITICAL_SECTION mutexM;
};

} // namespace Windows
} // namespace Os
