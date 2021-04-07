/**
 * 
 * Author: 		Iosif Haidu
 * Description: Interface for widget storage
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef __GUI_IWIDGETSTORAGE_H__
#define __GUI_IWIDGETSTORAGE_H__

#include "extern/imgui/imgui.h"
#include <gsl/pointers.h>

namespace GUI
{
namespace Storage
{

using gsl::not_null;

/**
 * Interface for widget storage using key-value pair.
 * Can render all widgets stored.
 * 'get()' not provided intentionally, to avoid exposing
 *      elements without synchronizing in multithread environment.
 * A derived class should provide different methods which process
 *      elements using an internal thread synchronization object.
 */
template <typename T>
class IWidgetStorage
{
public:
    using StorageKey = ImGuiID;

    IWidgetStorage()=default;
    virtual ~IWidgetStorage()=default;

    /**
     * Add a widget to storage.
     * 
     * @param  {T*} pWidgetP : widget to add
     * @return {StorageKey}  : key to identify widget in storage
     */
    virtual StorageKey add(not_null<T*> pWidgetP) = 0;
    
    /**
     * Remove widget from storage.
     * 
     * @param  {StorageKey} keyP : key of widget to be removed
     */
    virtual void remove(StorageKey keyP) = 0;

    /**
     * Number of element in storage.
     * 
     * @return {size_t}  : count of elements
     */
    virtual size_t count() const = 0;

    /**
     * Updates widget in storage based on key.
     * 
     * @param  {StorageKey} keyP : key of widget to be updated
     */
    virtual void update(StorageKey keyP) = 0;

    /**
     * Add child widget for a parent widget.
     * 
     * @param  {StorageKey} parentP : id of parent widger
     * @param  {not_null<T*} >      : child widget to be added
     * @return {bool}               : true if parent found, false otherwise
     */
    virtual bool addChildFor(StorageKey parentP, not_null<T*> pWidgetP) = 0;
};

} // namespace Storage
} // namespace GUI

#endif  // __GUI_IWIDGETSTORAGE_H__