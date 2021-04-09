/**
 * Author: 		Iosif Haidu
 * Description: Interface for thread
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include <functional>

namespace Os
{

using ThreadFunc = std::function<void* (void*)>;

/**
 * Interface for thread implementation
 */
class IThread
{
public:
    virtual ~IThread() = default;
    /**
     * Start thread.
     * 
     * @return {bool}  : true if succeded, false otherwise
     */
    virtual bool start() = 0;
    /**
     * Wait until thread is done
     */
    virtual void join() = 0;
    /**
     * Get thread id.
     * 
     * @return {unsigned}  : valid thread id when successfuly created.
     */
    virtual unsigned long int getId() const = 0;
    /**
     * Get thread name
     * 
     * @return {char*}  : thread name
     */
    virtual const char* getName() const = 0;
};

} // namespace Os
