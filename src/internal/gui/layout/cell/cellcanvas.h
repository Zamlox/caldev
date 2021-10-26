/**
 * Author: 		Iosif Haidu
 * Description: Content that can be drawn in a cell.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iwidget.h"

namespace GUI
{
namespace Layout
{

/**
 * Content to be displayed in a cell layout.
 * It's a wrapper on IWidget, to be able to add
 *  various functionalities. 
 */
class CellCanvas
{
public:
private:
    IWidget* pWidgetM;
};


} // namespace Layout
} // namesapce GUI
