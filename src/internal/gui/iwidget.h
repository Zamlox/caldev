/**
 * Author: 		Iosif Haidu
 * Description: Interface for widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IWIDGET_H__
#define __GUI_IWIDGET_H__

#include "internal/gui/imgui/common.h"

namespace GUI
{

/** Minimum size on x */
constexpr int MIN_SIZE_X{100};
/** Minimum size on y */
constexpr int MIN_SIZE_Y{100};

/**
 * Widget interface
 */
class IWidget
{
public:
    virtual ~IWidget() = default;
    
    /**
     * Get id of widget.
     * @return {Id}  : widget id
     */
    virtual Id getId() const = 0;
    /**
     * Set widget it.
     * @param  {Id} idP : widget id
     */
    virtual void setId(Id idP) = 0;
    /**
     * Render widget.
     */
    virtual void render() = 0;
};

} // namespace GUI

#endif // __GUI_IWIDGET_H__