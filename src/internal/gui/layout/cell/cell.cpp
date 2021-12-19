/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/layout/cell/cell.h"

namespace GUI::Layout {

Cell::Cell(CellFormat const &rFormatP)
    : childrenM{std::make_unique<CellsChildren>()}
    , Format(rFormatP)
{
}

Cell::~Cell()
{
    clearChildren();
}

void Cell::addChild(CellFormat const& rFormatP)
{
    if (childrenM) {
        childrenM->emplace_back(new Cell(rFormatP));
    }
}

void Cell::clearChildren()
{
    if (childrenM) {
        for (auto& rCell : *childrenM) {
            rCell.reset();
        }
        childrenM->clear();
    }
}

void Cell::positionWidget(Widgets& rWidgetsP)
{
    if (childrenM) {
        for (auto& rCell : *childrenM) {
            rCell->positionWidget(rWidgetsP);
        }
    }
    else
    {
        Widgets::DataType pWidget{rWidgetsP.data[rWidgetsP.index++]};
    }
}

} // namesapce GUI::Layout
