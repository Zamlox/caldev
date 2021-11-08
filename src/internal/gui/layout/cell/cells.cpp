/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/layout/cell/cells.h"

namespace GUI
{
namespace Layout
{

Cells::~Cells()
{
    clear();
}

int Cells::addCell(ICell* pCellP)
{
    cellsM.push_back(pCellP);
}

ICell* Cells::getCell(unsigned int indexP)
{
    if (indexP < cellsM.size())
    {
        return cellsM[indexP];
    }
    return nullptr;
}

void Cells::clear()
{
    for (auto* pCell : cellsM)
    {
        delete pCell;
    }
    cellsM.clear();
}

} // namespace Layout
} // namesapce GUI
