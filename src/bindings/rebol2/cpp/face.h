/**
 * Author: 		Iosif Haidu
 * Description: Face data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_FACE_H__
#define __BIND_REBOL2_FACE_H__

#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include "bindings/rebol2/cpp/effect.h"
#include "bindings/rebol2/cpp/edge.h"
#include "bindings/rebol2/cpp/font.h"
#include "bindings/rebol2/cpp/para.h"

namespace Bind
{
namespace Rebol2
{

struct Face;

using Panes     = std::vector<Face>;
using Rate      = std::variant<int, Time>;
using Options   = std::variant<
    Word,
    std::vector<Word>
>;
using Changes   = std::variant<
    Word,
    std::vector<Word>
>;

/**
 * Data structure for corresponding face object in Rebol2
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
    None<Edge>      edgeM;
    None<Font>      fontM;
    None<Para>      paraM;
    None<Rate>      rateM;
    None<bool>      showM;
    None<Options>   optionsM;
    None<Changes>   changesM;
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_FACE_H__