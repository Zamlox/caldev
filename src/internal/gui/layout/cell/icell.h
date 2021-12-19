/**
 * Author: 		Iosif Haidu
 * Description: Building block of layout system.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/layout/cell/celltype.h"
#include "internal/gui/layout/format/format.h"
#include "internal/gui/iwidget.h"
#include <memory>
#include <vector>

namespace GUI::Layout {

using CellFormat = Format<int>;

struct Widgets
{
    using DataType = std::shared_ptr<IWidget>;
    std::vector<DataType> data;
    int index;
};

class ICell
{
public:
    virtual ~ICell() = default;

    virtual void positionWidget(Widgets& rWidgetsP) = 0;

    virtual void addChild(CellFormat const& rFormatP) = 0;
    virtual void clearChildren() = 0;
};

} // namesapce GUI::Layout
