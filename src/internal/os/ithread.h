/**
 * Author: 		Iosif Haidu
 * Description: Interface for thread
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __OS_ITHREAD_H__
#define __OS_ITHREAD_H__

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
     * Create a thread which will execute function 'funcP'.
     * When this method returns the thread is already running.
     * 
     * @param  {char*} nameP          : thread name
     * @param  {ThreadFunc} funcInitP : function to be executed in thread before signaling caller
     * @param  {ThreadFunc} funcP     : function to be executed in thread after signaling caller
     * @param  {void*} pParamP        : parameter to be passed to funcInitP and funcP
     * @return {bool}                 : true if succeeded, false otherwise
     */
    virtual bool create(const char* nameP, ThreadFunc funcInitP, ThreadFunc funcP, void* pParamP) = 0;
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

#endif // __OS_ITHREAD_H__