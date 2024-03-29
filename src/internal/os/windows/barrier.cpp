/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/os/windows/barrier.h"
#include <stdio.h>
#include <stdlib.h>

namespace Os
{
namespace Windows
{

Barrier::Barrier()
{
    if ((eventM = CreateEvent(NULL, FALSE, FALSE, NULL)) == NULL)
    {
        fprintf(stderr, "ERROR ! Cannot create event !\n");
        exit(1);
    }
}

void Barrier::signal()
{
    if (!SetEvent(eventM))
    {
        fprintf(stderr, "ERROR ! Cannot set event !\n");
        exit(1);
    }
}

void Barrier::wait()
{
    if (WaitForSingleObject(eventM, INFINITE) == WAIT_FAILED)
    {
        fprintf(stderr, "ERROR ! Wait on event failed !\n");
        exit(1);
    }
}

} // namespace Windows
} // namespace Os
