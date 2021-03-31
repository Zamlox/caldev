/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "internal/gui/storage/windowstorage.h"
#include "internal/gui/imgui/common.h"

namespace GUI
{
namespace Storage
{

WindowStorage::StorageKey WindowStorage::add(not_null<IWindow*> pWindowP)
{
    Id id{pWindowP->getId()};
    storageM.add(id, pWindowP);
    return id;
}

} // namespace Storage
} // namespace GUI