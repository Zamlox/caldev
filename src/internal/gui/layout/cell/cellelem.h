/**
 * Author: 		Iosif Haidu
 * Description: Element type for cell.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/cellcanvas.h"
#include <vector>

#include <memory>
#include <vector>

namespace GUI
{
namespace Layout
{

class Cell;

union CellElem {
    std::vector<Cell*> cellsM;
    CellCanvas canvasM;
};


} // namespace Layout
} // namesapce GUI
