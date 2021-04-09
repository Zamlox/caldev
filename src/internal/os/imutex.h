/**
 * Author: 		Iosif Haidu
 * Description: Interface for mutex
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

namespace Os
{
/**
 * Interface for mutex 
 */
class IMutex
{
public:
    virtual ~IMutex() = default;
    /**
     * Lock mutex
     */
    virtual void lock() = 0;
    /**
     * Unlock mutex
     */
    virtual void unlock() = 0;
};

} // namespace OS
