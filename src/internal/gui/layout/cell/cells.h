/**
 * Author: 		Iosif Haidu
 * Description: A collection of cells (rows/columns) used in layout.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/icell.h"
#include <vector>

namespace GUI
{
namespace Layout
{

/**
 * Collection of cells used to define rows and columns
 */
class Cells
{
public:
    int addCell(const ICell& rCellP);
    ICell& getCell(int indexP);

private:
    std::vector<ICell*> cellsM;
};

} // namespace Layout
} // namesapce GUI
