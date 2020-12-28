/**
 * Author: 		Iosif Haidu
 * Description: Edge data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_EDGE_H__
#define __BIND_REBOL2_EDGE_H__

#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include "bindings/rebol2/cpp/effect.h"

namespace Bind
{
namespace Rebol2
{

struct Edge
{
    None<Color>     colorM;
    None<Pair>      sizeM;
    None<Effect>    effectM;
    None<Image>     imageM;
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_EDGE_H__