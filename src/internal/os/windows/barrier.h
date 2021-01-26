/**
 * Author: 		Iosif Haidu
 * Description: IBarrier implementation for Windows OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_WINDOWS_BARRIER_H__
#define __OS_WINDOWS_BARRIER_H__

#include "internal/os/ibarrier.h"
#include <windows.h>
#include <synchapi.h>

namespace Os
{
namespace Windows
{
/**
 * Impements IBarrier
 */
class Barrier : public IBarrier
{
public:
    Barrier();
    /** see IBarrier::signal() */
    virtual void signal() override;
    /** see IBarrier::wait() */
    virtual void wait() override;

private:
    HANDLE eventM;
};

} // namespace Windows
} // namespace Os

#endif //__OS_WINDOWS_BARRIER_H__