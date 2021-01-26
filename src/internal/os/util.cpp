/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/os/util.h"
#include <assert.h>

namespace Os
{

Util* Util::pInstanceM{nullptr};

Util& Util::instance()
{
    if (pInstanceM == nullptr)
    {
        pInstanceM = new Util;
    }
    return *pInstanceM;
}

void Util::usleep(unsigned int usecsP)
{
    assert(pInstanceM);
    pInstanceM->implM.usleep(usecsP);
}

void Util::msleep(unsigned int msecsP)
{
    assert(pInstanceM);
    pInstanceM->implM.msleep(msecsP);
}

void Util::sleep(unsigned int secsP)
{
    assert(pInstanceM);
    pInstanceM->implM.sleep(secsP);
}

} // namespace Os