/**
 * Author: 		Iosif Haidu
 * Description: Interface for barrier
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_IBARRIER_H__
#define __OS_IBARRIER_H__

namespace Os
{
/**
 * Interface for barrier implementation.
 */
class IBarrier
{
public:
    virtual ~IBarrier() = default;
    /**
     * Signal barrier to get out from 'wait()'
     */
    virtual void signal() = 0;
    /**
     * Wait until 'signal()' is called
     */
    virtual void wait() = 0;
};

} // namespace Os

#endif // __OS_IBARRIER_H__