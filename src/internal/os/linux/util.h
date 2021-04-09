/**
 * Author: 		Iosif Haidu
 * Description: Utility Os related functions
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/os/iutil.h"

namespace Os
{
namespace Linux
{
/**
 * Utility OS functions
 */
class Util : public IUtil
{
public:
    /** see IUtil::usleep() */
    void usleep(unsigned int usecsP) override;
    /** see IUtil::msleep() */
    void msleep(unsigned int msecsP) override;
    /** see IUtil::sleep() */
    void sleep(unsigned int secsP) override;
};

} // namespace Linux
} // namespace Os
