/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/resize.h"

namespace GUI
{

Resize::Resize()
    : startedM{false}
    , mouseHoveredTimestampM{0.0}
    , mouseDeltaM{0.0, 0.0}
{
}

bool Resize::getStarted() const
{
    return startedM;
}
void Resize::setStarted(bool valueP)
{
    startedM = valueP;
}

double Resize::getMouseHoveredTimestamp() const
{
    return mouseHoveredTimestampM;
}

void Resize::setMouseHoveredTimestamp(double valueP)
{
    mouseHoveredTimestampM = valueP;
}

ImVec2 Resize::getMouseDelta() const
{
    return mouseDeltaM;
}

void Resize::setMouseDelta(ImVec2 const& rMouseDeltaP)
{
    mouseDeltaM = rMouseDeltaP;
}

Resize& Resize::operator=(const Resize& rOpP)
{
    if (this != &rOpP)
    {
        startedM                = rOpP.startedM;
        mouseHoveredTimestampM  = rOpP.mouseHoveredTimestampM;
        mouseDeltaM             = rOpP.mouseDeltaM;
    }
    return *this;
}

} // namespace GUI
