/**
 * Author: 		Iosif Haidu
 * Description: Cross platform mutex implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/imutex.h"
#ifdef OS_WINDOWS
#include "internal/os/windows/mutex.h"
#else
#include "internal/os/linux/mutex.h"
#endif

namespace Os
{
/**
 * Cross platform implementation of mutex
 */
class Mutex : public IMutex
{
public:
    /** see IMutex::lock() */
    void lock() override;
    /** see IMutex::unlock() */
    void unlock() override;
    
private:
#ifdef OS_WINDOWS
    Os::Windows::Mutex implM;
#else
    Os::Linux::Mutex implM;
#endif
};

} // namespace Os
