/**
 * Copyright 2021 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/storage/widgetstorage.h"
#include "internal/gui/imgui/common.h"

namespace GUI
{
namespace Storage
{

WidgetStorage::StorageKey WidgetStorage::add(not_null<IWidget*> pWidgetP)
{
    Id id{pWidgetP->getId()};
    storageM.add(id, pWidgetP);
    return id;
}

} // namespace Storage
} // namespace GUI