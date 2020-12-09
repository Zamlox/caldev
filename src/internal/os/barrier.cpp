/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "barrier.h"

namespace Os
{

void Barrier::signal()
{
    implM.signal();
}

void Barrier::wait()
{
    implM.wait();
}

} // namespace Os