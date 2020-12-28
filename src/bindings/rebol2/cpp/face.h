/**
 * Author: 		Iosif Haidu
 * Description: Face data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_FACE_H__
#define __BIND_REBOL2_FACE_H__

#include "bindings/common.h"
#include <string>
#include <vector>
#include <cstddef>
#include <variant>

namespace Bind
{
namespace Rebol2
{

struct Face;
struct DrawItems;

using Text      = std::string;
using Word      = Text;
using PairInt   = std::tuple<int, int>;
using Pair      = PairInt;
using Panes     = std::vector<Face>;
using Color     = std::tuple<int, int, int>;
using Image     = std::vector<std::byte>;
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

/**
 * Data strutcture for corresponding face object in Rebol2
 */
struct Face
{
    int             idM;
    None<Word>      typeM;
    None<Pair>      offsetM;
    None<Pair>      sizeM;
    None<Pair>      spanM;
    None<Panes>     paneM;
    None<Text>      textM;
    None<Color>     colorM;
    None<Image>     imageM;
    None<Effect>    effectM;
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_FACE_H__