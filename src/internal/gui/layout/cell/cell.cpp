/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/layout/cell/cell.h"

namespace GUI
{
namespace Layout
{

Cell::Cell()
    : typeM{CellType::CELL_CANVAS}
{
    contentM.pCanvasM = nullptr;
}

Cell::~Cell()
{
    (typeM == CellType::CELL_CANVAS) ?
        delete contentM.pCanvasM :
        delete contentM.pCellsM;
}

int Cell::count() const
{
    return (typeM == CellType::CELL_CANVAS) ? 1 : contentM.pCellsM->count();
}

int Cell::addItem()
{
    int index{0};
    if (typeM == CellType::CELL_CANVAS)
    {
        if (!contentM.pCanvasM)
        {
            contentM.pCanvasM = new CellCanvas();
            assert(contentM.pCanvasM);
        }
    }
    else
    {
        if (!contentM.pCellsM)
        {
            contentM.pCellsM = new Cells();
            assert(contentM.pCellsM);
            ICell* pCell = new Cell();
            index = contentM.pCellsM->addCell(pCell);
        }
    }
    return index;
}

Cells* Cell::getItem(unsigned int indexP) const
{
    Cells* pCells
    if (typeM == CellType::CELL_CANVAS)
    {
        if (indexP  conte)
    }
}

void Cell::draw()
{
    
}

} // namespace Layout
} // namesapce GUI
