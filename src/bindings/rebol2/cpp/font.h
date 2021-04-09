/**
 * Author: 		Iosif Haidu
 * Description: Font data structure 
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/tools/safemap.h"
#include "internal/gui/imgui/common.h"
extern "C"
{
#include "extern/rebsdev/src/glue/glue.h"
}

namespace Bind
{
namespace Rebol2
{

using Text      = std::string;

using FontInfo = struct {
    GUI::Font*  pFontM;
    FaceFont    faceFontM;
};
using FontsMap = Tools::SafeMap<std::string, FontInfo>;

} // namespace Rebol2
} // namespace Bind

bool operator ==(FaceFont const& rOp1P, FaceFont const& rOp2P);
bool operator !=(FaceFont const& rOp1P, FaceFont const& rOp2P);
