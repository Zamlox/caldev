/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/tools/logic.h"

namespace Logic
{

bool check::showErrMsgM{true};

check::check(int errorCodeSuccessP) 
    : errorCodeM{errorCodeSuccessP}
    , errResultM{std::make_tuple(SUCCESS, MSG_SUCCESS)}
{
}

check& check::error_if_true(bool conditionP, int errorCodeP, const char* errMsgP)
{
    if (conditionP && (errorCodeM == SUCCESS))
    {
        if (showErrMsgM)
        {
            fprintf(stderr, errMsgP);
        }
        errorCodeM = errorCodeP;
    }
    return *this;
}

check& check::error_if_true(bool conditionP)
{
    if (conditionP && errorCodeM == SUCCESS)
    {
        if (showErrMsgM)
        {
            fprintf(stderr, std::get<const char*>(errResultM));
        }
        errorCodeM = std::get<int>(errResultM);
    }
    return *this;
}

check& check::execute_if_no_error(std::function<ErrResult(void)> rFP)
{
    if (errorCodeM == SUCCESS)
    {
        errResultM = rFP();
        errorCodeM = std::get<int>(errResultM);
    }
    return *this;
}

int check::result()
{
    return errorCodeM;
}

check::ErrResult check::make_error(int errCodeP, const char* errMsgP)
{
    return std::make_tuple(errCodeP, errMsgP);
}

check::ErrResult check::success()
{
    return make_error(SUCCESS, MSG_SUCCESS);
}

void check::showErrorMsg(bool valueP)
{
    showErrMsgM = valueP;
}



} // namespace Logic
