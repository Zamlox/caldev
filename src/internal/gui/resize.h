/**
 * Author: 		Iosif Haidu
 * Description: Implementation of IResize
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/iresize.h"

namespace GUI
{

constexpr int COUNT_BORDERS{4};
constexpr int COUNT_CORNERS{4};

/**
 * Implementation of IResize
 */
class Resize : public IResize
{
public:
    Resize();
    /** see IResize::getStarted() */
    bool getStarted() const override;
    /** see IResize::setStarted() */
    void setStarted(bool valueP) override;
    /** see IResize::getMouseHoveredTimestamp() */
    double getMouseHoveredTimestamp() const override;
    /** see IResize::setMouseHoveredTimestamp() */
    void setMouseHoveredTimestamp(double valueP) override;
    /** see IResize::getMouseDelta() */
    ImVec2 getMouseDelta() const override;
    /** see IResize::setMouseDelta() */
    void setMouseDelta(ImVec2 const& rMouseDeltaP) override;

private:
    /** Resize operation started */
    bool    startedM;
    /** Timestamp of mouse when hovering over border/corner */
    double  mouseHoveredTimestampM;
    /** Delta value of mouse position */
    ImVec2  mouseDeltaM;

};

} // namespace GUi