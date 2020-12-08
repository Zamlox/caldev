/**
 * Author: 		Iosif Haidu
 * Description: Cross platform barrier implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_BARRIER_H__
#define __OS_BARRIER_H__

#include "ibarrier.h"
#ifdef OS_LINUX
#include "linux/barrier.h"
#endif

namespace Os 
{
/**
 * Cross platform implementation of barrier
 */
class Barrier : public IBarrier
{
public:
    /** see IBarrier::signal() */
    virtual void signal() override;
    /** see IBarrier::wait() */
    virtual void wait() override;

private:
#ifdef OS_LINUX
    Os::Linux::Barrier implM;
#endif
};

} // namespace Os

#endif // __OS_BARRIER_H__