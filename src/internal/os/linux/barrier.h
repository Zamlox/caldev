/**
 * Author: 		Iosif Haidu
 * Description: IBarrier implementation for Linux OS
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_LINUX_BARRIER_H__
#define __OS_LINUX_BARRIER_H__

#include "ibarrier.h"
#include <semaphore.h>

namespace Os
{
namespace Linux
{

class Barrier : public IBarrier
{
public:
    Barrier();
    /** see IBarrier::signal() */
    virtual void signal() override;
    /** see IBarrier::wait() */
    virtual void wait() override;

private:
    sem_t semaphoreM;
};

} // namespace Linux
} // namespace Os

#endif // __OS_LINUX_BARRIER_H__