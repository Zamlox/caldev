/**
 * Author: 		Iosif Haidu
 * Description: Conversion of parameter stream
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

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
