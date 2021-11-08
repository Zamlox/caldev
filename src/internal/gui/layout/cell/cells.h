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
    ~Cells();

    int count() const;
    int addCell(ICell* pCellP);
    ICell* getCell(unsigned int indexP);
    void clear();

private:
    std::vector<ICell*> cellsM;
};

inline int Cells::count() const 
{
    return cellsM.size();
}

} // namespace Layout
} // namesapce GUI
