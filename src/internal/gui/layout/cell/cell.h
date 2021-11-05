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
 */
class Cell : public ICell
           , public CellFormat
{
public:
    Cell();

    void setFormat(const CellFormat& rFormatP) override;
    Cells* getRows() override;
    Cells* getCols() override;

private:
    Cells* getCells(CellType typeP);

    CellType typeM;
    CellElem contentM;
};

inline void Cell::setFormat(const CellFormat& rFormatP)
{
    CellFormat* pFormat{static_cast<CellFormat*>(this)};
    *pFormat = rFormatP;
}

inline Cells* Cell::getRows()
{
    return getCells(CellType::CELL_ROWS);
}

inline Cells* Cell::getCols()
{
    return getCells(CellType::CELL_COLS);
}

inline Cells* Cell::getCells(CellType typeP)
{
    return (typeM == typeP) ? contentM.cellsM.get() : nullptr;
}

} // namespace Layout
} // namesapce GUI
