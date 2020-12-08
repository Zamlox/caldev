/**
 * Author: 		Iosif Haidu
 * Description: Cross platform utility functions implementation
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_UTIL_H__
#define __OS_UTIL_H__

#include "iutil.h"
#ifdef OS_LINUX
#include "linux/util.h"
#endif

namespace Os
{

/**
 * Cross platform implementation of IUtil
 */
class Util: public IUtil
{
public:
    /**
     * Creates a unique instance of Util
     * 
     * @return {Util}  : instance of Util
     */
    static Util& instance();

    /** see IUtil::usleep() */
    void usleep(unsigned int usecsP) override;
    /** see IUtil::msleep() */
    void msleep(unsigned int msecsP) override;
    /** see IUtil::sleep() */
    void sleep(unsigned int secsP) override;
    
private:
    Util() = default;

#ifdef OS_LINUX
    Os::Linux::Util implM;
#endif
    static Util* pInstanceM;
};

} // namespace Os

#endif // __OS_UTIL_H__