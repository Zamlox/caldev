/**
 * Author: 		Iosif Haidu
 * Description: Window storage thread safe
 *
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#ifndef WINDOWSTORAGE_H
#define WINDOWSTORAGE_H

#include "internal/gui/storage/basewidgetstorage.h"
#include "internal/gui/iwindow.h"

namespace GUI
{
namespace Storage
{

/**
 * Storage for windows
 */
class WindowStorage : public BaseWidgetStorage<IWindow>
{
public:
    using BaseType = BaseWidgetStorage<IWindow>;
    using StorageKey = typename BaseType::StorageKey;

    WindowStorage()=default;
    virtual ~WindowStorage()=default;

    /** see IWidgetStorage::add() */
    StorageKey add(not_null<IWindow*> pWindowP) override;
    /** see IWidgetStorage::remove() */
    void remove(StorageKey idP) override;
    /** see IWidgetStorage::count() */
    size_t count() const override;
};

} // namespace Storage
} // namespace Gui

#endif // WINDOWSTORAGE_H
