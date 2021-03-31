/**
 * Author: 		Iosif Haidu
 * Description: Widget storage thread safe
 *
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#pragma once

#include "internal/gui/storage/basewidgetstorage.h"
#include "internal/gui/iwidget.h"

namespace GUI
{
namespace Storage
{

/**
 * Storage for widgets
 */
class WidgetStorage : public BaseWidgetStorage<IWidget>
{
public:
    using BaseType = BaseWidgetStorage<IWidget>;
    using StorageKey = typename BaseType::StorageKey;

    WidgetStorage()=default;
    virtual ~WidgetStorage()=default;

    /** see IWidgetStorage::add() */
    StorageKey add(not_null<IWidget*> pWidgetP) override;
};

} // namespace Storage
} // namespace Gui
