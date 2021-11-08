/**
 * Author: 		Iosif Haidu
 * Description: Building block of layout system.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/celltype.h"
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

    virtual void setType(CellType typeP) = 0;
    virtual CellType getType() const = 0;
    virtual void setFormat(const CellFormat& rFormatP) = 0;
    virtual int count() const = 0;
    virtual int addItem() = 0;
    virtual ICell* getCell(unsigned int indexP) const = 0;
    virtual void draw() = 0;
};

} // namespace Layout
} // namesapce GUI
