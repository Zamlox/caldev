/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "mutex.h"

namespace Os
{

void Mutex::lock()
{
    implM.lock();
}

void Mutex::unlock()
{
    implM.unlock();
}


} // namespace Os