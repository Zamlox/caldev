/**
 * Author: 		Iosif Haidu
 * Description: Interface for resizing widgets
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "extern/imgui/imgui.h"

namespace GUI
{

class IResize
{
public:
    IResize() = default;
    virtual ~IResize() = default;
    /**
     * Check if a resize operation started.
     * 
     * @return {bool}  : true if resize started, false otherwise
     */
    virtual bool getStarted() const = 0;
    /**
     * Set started a resize operation.
     * 
     * @param  {bool} valueP : value for started operation
     */
    virtual void setStarted(bool valueP) = 0;
    /**
     * Get timestamp of mouse hovered over widget.
     * 
     * @return {double}  : timestamp value
     */
    virtual double getMouseHoveredTimestamp() const = 0;
    /**
     * Set timestamp value of mouse hovering over a widget.
     * 
     * @param  {double} valueP : timestamp value
     */
    virtual void setMouseHoveredTimestamp(double valueP) = 0;
    /**
     * Get delta value of mouse position.
     * 
     * @return {ImVec2}  : delat value
     */
    virtual ImVec2 getMouseDelta() const = 0;
    /**
     * Set delta value of mouse position.
     * 
     * @param  {ImVec2} const : delta value 
     */
    virtual void setMouseDelta(ImVec2 const& rMouseDeltaP) = 0;
};

} // namespace GUI
