/**
 * Author: 		Iosif Haidu
 * Description: Building block of layout system.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/celltype.h"
#include "internal/gui/layout/cell/cellelem.h"
#include "internal/gui/layout/format/format.h"

namespace GUI
{
namespace Layout
{

using CellFormat = Format<int>;

/**
 * Building block for layout.
 * A layout is a collection of cells as rows and/or columns.
 * Rows/columns can be embedded one into another, the leaf
 *  element must be a Canvas type so something is displayed
 *  insisde the cell.
 * Must be able to allow formatting content (alignment, margin, ...)
 */
class Cell 
{
public:
    Cell(const CellFormat& rCellFormatP);

private:
    CellType typeM;
    CellElem cellM;

    /** Format content of cell */
    CellFormat formatM;
};

} // namespace Layout
} // namesapce GUI
