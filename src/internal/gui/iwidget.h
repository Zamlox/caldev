/**
 * Author: 		Iosif Haidu
 * Description: Interface for widgets
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IWIDGET_H__
#define __GUI_IWIDGET_H__

#include "imgui.h"

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
     * @return {ImGuiID}  : widget id
     */
    virtual ImGuiID getId() const = 0;
    /**
     * Set widget it.
     * @param  {ImGuiID} idP : widget id
     */
    virtual void setId(ImGuiID idP) = 0;
    /**
     * Render widget.
     */
    virtual void render() = 0;
};

} // namespace GUI

#endif /7 __GUI_IWIDGET_H__