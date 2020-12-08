/**
 * Author: 		Iosif Haidu
 * Description: Cross platform mutex implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_MUTEX_H__
#define __OS_MUTEX_H__

#include "imutex.h"
#ifdef OS_LINUX
#include "linux/mutex.h"
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
#ifdef OS_LINUX
    Os::Linux::Mutex implM;
#endif
};

} // namespace Os

#endif // __OS_MUTEX_H__