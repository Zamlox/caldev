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
    if (sem_init(&semaphoreM, 0, 0) != 0) {
        printf("\n Semaphore init has failed\n");
        exit(1);
    }
}

void Barrier::signal()
{
    sem_post(&semaphoreM);
}

void Barrier::wait()
{
    sem_wait(&semaphoreM);
}

} // namespace Linux
} // namespace Os