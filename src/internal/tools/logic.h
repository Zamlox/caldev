/**
 * Author: 		Iosif Haidu
 * Description: Various logic related functions and classes
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __TOOLS_LOGIC_H__
#define __TOOLS_LOGIC_H__

#include <stdio.h>

namespace Logic
{

/**
 * And logic between all arguments
 * @return {bool}         : 
 */
template<typename... Args>
bool all(Args... args) 
{ 
    return (... && args); 
}

/**
 * Implements helper functions in a functional programming style.
 */
class check
{
public:
    check(int errorCodeSuccessP) : errorCodeM{errorCodeSuccessP}
    {}

    /**
     * If condition is true sets error code to errorCodeP and prints message errMSgP
     * 
     * @param  {bool} conditionP : condition to be checked
     * @param  {int} errorCodeP  : error code to report
     * @param  {char*} errMsgP   : error message to be printed
     * @return {check}           : itself
     */
    check& error_if_true(bool conditionP, int errorCodeP, const char* errMsgP)
    {
        if (conditionP && errorCodeM == 0)
        {
            fprintf(stderr, errMsgP);
            errorCodeM = errorCodeM;
        }
        return *this;
    }

    /**
     * Get result of error_if_true
     * 
     * @return {int}  : error code set by error_if_true
     */
    int result()
    {
        return errorCodeM;
    }

private:
    /** Error code to report */
    int errorCodeM;
};

} // namespace Logic

#endif // __TOOLS_LOGIC_H__