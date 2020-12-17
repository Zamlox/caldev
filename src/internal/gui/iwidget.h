/**
 * Author: 		Iosif Haidu
 * Description: Interface for widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IWIDGET_H__
#define __GUI_IWIDGET_H__

#include "imgui/common.h"

namespace GUI
{
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