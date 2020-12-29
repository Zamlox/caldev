/**
 * Author: 		Iosif Haidu
 * Description: Para data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_PARA_H__
#define __BIND_REBOL2_PARA_H__

#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include <vector>
#include <variant>

namespace Bind
{
namespace Rebol2
{

using ParaTabsBlock = std::vector<int>;
using ParaTabs = std::variant<
    int,
    ParaTabsBlock
>;

struct Para
{
    CanBeNone<Pair>      originM;
    CanBeNone<Pair>      marginM;
    CanBeNone<Pair>      indentM;
    CanBeNone<Pair>      scrollM;
    CanBeNone<ParaTabs>  tabsM;
    CanBeNone<bool>      wrapM;
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_PARA_H__