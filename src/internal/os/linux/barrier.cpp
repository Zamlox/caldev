/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "barrier.h"
#include <stdio.h>
#include <stdlib.h>

namespace Os
{
namespace Linux
{

Barrier::Barrier()
{
#ifdef OS_LINUX
    if (sem_init(&semaphoreM, 0, 0) != 0) {
        printf("\n Semaphore init has failed\n");
        exit(1);
    }
#else
    if ((pSemaphoreM = dispatch_semaphore_create(0)) == nullptr)
    {
        printf("\n Semaphore create has failed\n");
        exit(1);
    }
#endif
}

Barrier::~Barrier()
{
#ifdef OS_LINUX
    sem_destroy(&semaphoreM);
#else
    dispatch_release(pSemaphoreM);
#endif
}

void Barrier::signal()
{
#ifdef OS_LINUX
    sem_post(&semaphoreM);
#else
    dispatch_semaphore_signal(pSemaphoreM);
#endif
}

void Barrier::wait()
{
#ifdef OS_LINUX
    sem_wait(&semaphoreM);
#else
    dispatch_semaphore_wait(pSemaphoreM, DISPATCH_TIME_FOREVER);
#endif
}

} // namespace Linux
} // namespace Os