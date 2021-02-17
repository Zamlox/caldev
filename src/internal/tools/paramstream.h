/**
 * Author: 		Iosif Haidu
 * Description: Conversion of parameter stream
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __TOOLS_PARAMSTREAM_H__
#define __TOOLS_PARAMSTREAM_H__

#include <string>

namespace Tools
{



class ParamStreamIn
{
public:
    ParamStreamIn(const char* streamP);

    bool getToken(int& rTypeP, );

private:
    std::string inputM;
};

} // namespace Tools

#endif // __TOOLS_PARAMSTREAM_H__