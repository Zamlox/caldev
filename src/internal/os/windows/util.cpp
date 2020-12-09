/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "util.h"
#include <synchapi.h>

namespace Os
{
namespace Windows
{

void Util::usleep(unsigned int usecsP)
{
    // TODO: Implement later
    // ...
}

void Util::msleep(unsigned int msecsP)
{
    Sleep(msecsP);
}

void Util::sleep(unsigned int secsP)
{
    msleep(secsP * 1000);
}

} // namespace Windows
} // namespace Os