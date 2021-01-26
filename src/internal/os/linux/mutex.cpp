/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/os/linux/mutex.h"
#include <stdio.h>
#include <stdlib.h>

namespace Os
{
namespace Linux
{

Mutex::Mutex()
{
    pthread_mutexattr_init(&mutexAttrM);
    pthread_mutexattr_settype(&mutexAttrM, PTHREAD_MUTEX_RECURSIVE);
    if (pthread_mutex_init(&mutexM, &mutexAttrM) != 0) {
        fprintf(stderr, "Mutex init has failed\n");
        exit(1);
    }
}

Mutex::~Mutex()
{
    pthread_mutex_destroy(&mutexM);
}

void Mutex::lock()
{
    pthread_mutex_lock(&mutexM);
}

void Mutex::unlock()
{
    pthread_mutex_unlock(&mutexM);
}

} // namespace Linux
} // namespace Os