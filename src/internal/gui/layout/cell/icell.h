/**
 * Author: 		Iosif Haidu
 * Description: Building block of layout system.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/format/format.h"

namespace GUI
{
namespace Layout
{

using CellFormat = Format<int>;

class Cells;

class ICell
{
public:
    virtual ~ICell() = default;

    virtual void setFormat(const CellFormat& rFormatP) = 0;
    virtual Cells* getRows() = 0;
    virtual Cells* getCols() = 0;
};

} // namespace Layout
} // namesapce GUI
