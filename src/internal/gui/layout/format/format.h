/*
 * Created by Iosif Haidu on 29/11/2021.
 * Copyright (c) 2021 Iosif Haidu. All rights reserved.
 *
 * Description: Format values for cell layout
 */

#pragma once

#include "internal/gui/layout/format/alignment.h"
#include <tuple>

namespace GUI::Layout {

template <typename T>
class Format {
public:
    Format()
        : padM{}
        , marginHorizM{}
        , marginVertM{}
        , horizAlignM{HorizAlign::CENTER}
        , vertAlignM{VertAlign::CENTER}
        , heightM{}
        , widthM{}
    {}
    Format(Format const& rFormatP)
    {
        *this = rFormatP;
    }

    void setPad(T valueP)
    {
        padM = valueP;
    }
    T getPad() const
    {
        return padM;
    }
    void setMarginHoriz(T leftP, T rightP)
    {
        std::get<0>(marginHorizM) = leftP;
        std::get<1>(marginHorizM) = rightP;
    }
    std::tuple<T, T> getMarginHoriz() const
    {
        return marginHorizM;
    }
    void setMarginVert(T topP, T bottomP)
    {
        std::get<0>(marginVertM) = topP;
        std::get<1>(marginVertM) = bottomP;
    }
    std::tuple<T, T> getMarginVert() const
    {
        return marginVertM;
    }
    void setAlignHoriz(HorizAlign alignP)
    {
        horizAlignM = alignP;
    }
    HorizAlign getHorizAlign() const
    {
        return horizAlignM;
    }
    void setAlignVert(VertAlign alignP)
    {
        vertAlignM = alignP;
    }
    VertAlign getAlignVert() const
    {
        return vertAlignM;
    }
    void setHeight(T valueP)
    {
        heightM = valueP;
    }
    T getHeight() const
    {
        return heightM;
    }
    void setWidth(T valueP)
    {
        widthM = valueP;
    }
    T getWidth() const
    {
        return widthM;
    }

    Format<T>& operator=(Format<T> const& rValueP)
    {
        if (&rValueP != this) {
            padM = rValueP.padM;
            marginHorizM = rValueP.marginHorizM;
            marginVertM = rValueP.marginVertM;
            horizAlignM = rValueP.horizAlignM;
            vertAlignM = rValueP.vertAlignM;
            heightM = rValueP.heightM;
            widthM = rValueP.widthM;
        }
        return *this;
    }

protected:
    T padM;
    std::tuple<T, T> marginHorizM;
    std::tuple<T, T> marginVertM;
    HorizAlign horizAlignM;
    VertAlign vertAlignM;
    T heightM;
    T widthM;
};

} // namespace Gui::Layout
