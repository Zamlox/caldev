/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "util.h"
#include <unistd.h>

namespace Os
{
namespace Linux
{

void Util::usleep(unsigned int usecsP)
{
    ::usleep(usecsP);
}

void Util::msleep(unsigned int msecsP)
{
    this->usleep(msecsP * 1000);
}

void Util::sleep(unsigned int secsP)
{
    ::sleep(secsP);
}

} // namespace Linux
} // namespace Os