/**
 * Author: 		Iosif Haidu
 * Description: Element type for cell.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/cellcanvas.h"
#include "internal/gui/layout/cell/cells.h"

namespace GUI
{
namespace Layout
{

class Cell;

union CellElem {
    Cells* pCellsM;
    CellCanvas* pCanvasM;
};

} // namespace Layout
} // namesapce GUI
