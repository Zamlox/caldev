/**
 * Author: 		Iosif Haidu
 * Description: Effect data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_EFFECT_H__
#define __BIND_REBOL2_EFFECT_H__

#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include <variant>

namespace Bind
{
namespace Rebol2
{

struct DrawItems;
using EffectParams  = std::variant<
    Param0,
    Param2<Pair, Pair>,
    Param1<Pair>,
    Param1<int>,
    Param1<Color>,
    Param3<Pair, Color, Color>,
    Param1<std::vector<DrawItems>>,
    Param2<Color, double>,
    Param4<Pair, Color, int, int>,
    Param5<Pair, Pair, Color, int, Pair>
>;
using Effect    = std::variant<
    Word,
    std::vector<std::tuple<Word, EffectParams>>
>;

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_EFFECT_H__