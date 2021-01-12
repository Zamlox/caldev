/**
 * Author: 		Iosif Haidu
 * Description: Various logic related functions and classes
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __TOOLS_LOGIC_H__
#define __TOOLS_LOGIC_H__

#include "internal/errors/errors.h"
#include <stdio.h>
#include <tuple>
#include <functional>

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
 * Implements helper functions.
 */
class check
{
public:
    using ErrResult = std::tuple<int, const char*>;

    check(int errorCodeSuccessP) ;

    /**
     * If condition is true sets error code to errorCodeP and prints message errMSgP
     * 
     * @param  {bool} conditionP : condition to be checked
     * @param  {int} errorCodeP  : error code to report
     * @param  {char*} errMsgP   : error message to be printed
     * @return {check}           : itself
     */
    check& error_if_true(bool conditionP, int errorCodeP, const char* errMsgP);
    /**
     * Call this function after execute(std::function<ErrResult(void)>& rFP)
     * to use error code and message from return value of rFP().
     * 
     * @param  {bool} conditionP : condition to be checked
     * @return {check}           : itself
     */
    check& error_if_true(bool conditionP);
    /**
     * Call this function to execute rFP which return error code and message.
     * rFP will be executed if no previous errors were reported.
     * 
     * @param  {std::function<ErrResult(void)>} rFP : function to be called
     * @return {check}                              : itself
     */
    check& execute_if_no_error(std::function<ErrResult(void)> rFP);
    /**
     * Get result of error_if_true
     * 
     * @return {int}  : error code set by error_if_true
     */
    int result();
    /**
     * Helper to create error result
     * 
     * @param  {int} errCodeP  : error code
     * @param  {char*} errMsgP : error message
     * @return {ErrResult}     : tuple of error code and message
     */
    static ErrResult make_error(int errCodeP, const char* errMsgP);
    /**
     * Helper for creating success error result
     * 
     * @return {ErrResult}  : tuple of error code and message
     */
    static ErrResult success();
    /**
     * Set flag to display error mesasge.
     * 
     * @param  {bool} valueP : true to display error message, false otherwise
     */
    static void showErrorMsg(bool valueP);

private:
    /** Error code to report */
    int errorCodeM;
    /** Result embedding error code and message in a tuple */
    ErrResult errResultM;
    /** Flag indicating if error message shhould be displayed */
    static bool showErrMsgM;
};

} // namespace Logic

#endif // __TOOLS_LOGIC_H__