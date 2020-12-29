/**
 * Author: 		Iosif Haidu
 * Description: Base types for face
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_BASE_H__
#define __BIND_REBOL2_BASE_H__

#include "bindings/common.h"
#include <string>
#include <vector>
#include <cstddef>

namespace Bind
{
namespace Rebol2
{

using Text      = std::string;
using Word      = Text;
using PairInt   = std::tuple<int, int>;
using Pair      = PairInt;
using Color     = std::tuple<int, int, int>;
using Image     = std::vector<std::byte>;
using Time      = std::string;

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_BASE_H__