/**
 * Author: 		Iosif Haidu
 * Description: Draw data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_DRAW_H__
#define __BIND_REBOL2_DRAW_H__

#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include <vector>
#include <variant>

namespace Bind
{
namespace Rebol2
{

// TODO: refactor based on description from: http://www.rebol.com/docs/draw-ref.html
using DrawItems = std::vector<Word>; 

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_DRAW_H__