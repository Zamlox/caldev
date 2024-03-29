/**
 * Author: 		Iosif Haidu
 * Description: IBarrier implementation for Linux OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/ibarrier.h"
#ifdef OS_LINUX
#include <semaphore.h>
#else
#include <dispatch/dispatch.h>
#endif

namespace Os
{
namespace Linux
{

class Barrier : public IBarrier
{
public:
    Barrier();
    ~Barrier();
    /** see IBarrier::signal() */
    virtual void signal() override;
    /** see IBarrier::wait() */
    virtual void wait() override;

private:
#ifdef OS_LINUX
    sem_t semaphoreM;
#else
    dispatch_semaphore_t pSemaphoreM;
#endif
};

} // namespace Linux
} // namespace Os
