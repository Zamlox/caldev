/**
 * Author: 		Iosif Haidu
 * Description: Element type for cell.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/cellcanvas.h"
#include "internal/gui/layout/cell/cells.h"
#include <memory>
#include <vector>

namespace GUI
{
namespace Layout
{

class Cell;

union CellElem {
    std::unique_ptr<Cells> cellsM;
    std::unique_ptr<CellCanvas> canvasM;
};


} // namespace Layout
} // namesapce GUI
