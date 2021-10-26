/**
 * Author: 		Iosif Haidu
 * Description: Format type.
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */
#pragma once

#include <tuple>

namespace GUI
{
namespace Layout
{

/**
 * Format attributes.
 */
template <typename T>
class Format
{
public:
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

private:
    T padM;
    std::tuple<T, T> marginHorizM;
    std::tuple<T, T> marginVertM;
    HorizAlign horizAlignM;
    VertAlign vertAlignM;
    T heightM;
    T widthM;
};

} // namespace Layout
} // namespace GUI