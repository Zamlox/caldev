/**
 * Author: 		Iosif Haidu
 * Description: A collection of cells (rows/columns) used in layout.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/icell.h"
#include <memory>
#include <vector>

namespace GUI::Layout {

using CellsChildren = std::vector<std::unique_ptr<ICell>>;

/**
 * Collection of cells used to define rows and columns
 */
class Cell : public ICell
           , public CellFormat
{
public:
    Cell(CellFormat const &rFormatP);
    ~Cell();

    void positionWidget(Widgets& rWidgetsP) override;

    void addChild(CellFormat const& rFormatP) override;
    void clearChildren() override;

private:
    std::unique_ptr<CellsChildren> childrenM;
};

} // namesapce GUI::Layout
