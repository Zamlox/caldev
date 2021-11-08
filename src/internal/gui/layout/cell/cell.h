/**
 * Author: 		Iosif Haidu
 * Description: Building block of layout system.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/icell.h"
#include "internal/gui/layout/cell/celltype.h"
#include "internal/gui/layout/cell/cellelem.h"
#include "internal/gui/layout/format/format.h"

namespace GUI
{
namespace Layout
{

/**
 * Building block for layout.
 * A layout is a collection of cells as rows and/or columns.
 * Rows/columns can be embedded one into another, the leaf
 *  element must be a Canvas type so something is displayed
 *  insisde the cell.
 * Must be able to allow formatting content (alignment, margin, ...)
 * 
 * Use this class by creating first all needed cells (rows, cols, canvas)
 * then apply it on a list of given widgets. All layouts starts with a 
 * single cell which can contain a canvas or rows/cols of other cells.
 * Something like:
 *  void doLayout(Cell* pCellP)
 *  {
 *     assert(pCellP);
 *     for (unsigned int i = 0; i < pCellP->count(); i++)
 *     {
 *         if (pCellP->getType() == CellType::CELL_CANVAS)
 *         {
 *             pCellP->draw();
 *         }
 *         else
 *         {
 *             Cells* pCells = pCellP->getCells();
 *             assert(pCells);
 *             for (unsigned int j = 0; j < pCells->count(); j++)
 *             {
 *                 doLayout(pCells->getCell(j));
 *             }
 *         }
 *     }
 *  }
 *  ICell* pCell = layout.getCell(0);
 *  doLayout(pCell);
 */
class Cell : public ICell
           , public CellFormat
{
public:
    Cell();
    ~Cell();

    void setType(CellType typeP) override;
    virtual CellType getType() const override;
    void setFormat(const CellFormat& rFormatP) override;

    int count() const override;
    int addItem() override; 
    ICell* getCell(unsigned int indexP) const override;

    void draw() override;

private:
    CellType typeM;
    CellElem contentM;
};

inline void Cell::setType(CellType typeP)
{
    typeM = typeP;
}

inline CellType Cell::getType() const
{
    return typeM;
}

inline void Cell::setFormat(const CellFormat& rFormatP)
{
    CellFormat* pFormat{static_cast<CellFormat*>(this)};
    *pFormat = rFormatP;
}

} // namespace Layout
} // namesapce GUI
