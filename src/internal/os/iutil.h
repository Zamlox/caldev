/**
 * Author: 		Iosif Haidu
 * Description: Interface for utility functions
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_IUTIL_H__
#define __OS_IUTIL_H__

namespace Os
{
/**
 * Utility functions interface
 */
class IUtil
{
public:
    virtual ~IUtil() = default;
    /**
     * Sleep for specified microseconds.
     * 
     * @param  {unsigned} int : microseconds to sleep
     */
    virtual void usleep(unsigned int usecsP) = 0;
    /**
     * Sleep for specified milliseconds
     * 
     * @param  {unsigned} int : milliseconds to sleep
     */
    virtual void msleep(unsigned int msecsP) = 0;
    /**
     * Sleep for specified seconds
     * 
     * @param  {unsigned} int : seconds to sleep
     */
    virtual void sleep(unsigned int secsP) = 0;
};

} // namespace Os

#endif // __OS_IUTIL_H__