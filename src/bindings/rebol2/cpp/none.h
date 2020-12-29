/**
 * Author: 		Iosif Haidu
 * Description: None related types
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __BIND_REBOL2_NONE_H__
#define __BIND_REBOL2_NONE_H__

#include "bindings/common.h"

namespace Bind
{
namespace Rebol2
{

constexpr void* none = nullptr;

template <typename T>
class CanBeNone : public Param1<T>
{
public:
    template <typename TDefault>
    T const& getValueOrDefault(TDefault const& rDefaultP) const
    {
        if (T* pVal = Param1<T>::getValue1(); pVal != nullptr)
        {
            return *pVal;
        }
        return rDefaultP;
    }

    CanBeNone& operator=(T const& rOpP)
    {
        Param1<T>::setValue1(rOpP);
        return *this;
    }
};

} // namespace Rebol2
} // namespace Bind

#endif // __BIND_REBOL2_NONE_H__