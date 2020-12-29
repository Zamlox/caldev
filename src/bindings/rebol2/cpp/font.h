/**
 * Author: 		Iosif Haidu
 * Description: Font data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_FONT_H__
#define __BIND_REBOL2_FONT_H__

#include "bindings/common.h"
#include "bindings/rebol2/cpp/base.h"
#include <vector>
#include <variant>

namespace Bind
{
namespace Rebol2
{

using FontStyleBlock = std::vector<Word>;
using FontStyle = std::variant<
    Word,
    FontStyleBlock
>;

struct Font
{
    CanBeNone<Text>      nameM;
    CanBeNone<Pair>      sizeM;
    CanBeNone<FontStyle> styleM;
    CanBeNone<Color>     colorM;
    CanBeNone<Word>      alignM;
    CanBeNone<Word>      valignM;
    CanBeNone<Pair>      offsetM;
    CanBeNone<Pair>      spaceM;
    CanBeNone<Pair>      shadowM;
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_FONT_H__