/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "internal/gui/storage/windowstorage.h"
#include "internal/gui/window.h"

namespace
{

TEST(WidgetStorage, Operations)
{
    GUI::Storage::WindowStorage storage;
    GUI::Storage::WindowStorage::StorageKey key1;
    GUI::Storage::WindowStorage::StorageKey key2;
    GUI::Window window{"dummy", 0, nullptr};
    key1 = storage.add(&window);
    EXPECT_NE(key1,  0);
    EXPECT_EQ(storage.count(), 1);
    key2 = storage.add(&window);
    EXPECT_NE(key2,  0);
    EXPECT_EQ(storage.count(), 1);
    storage.remove(key2);
    EXPECT_EQ(storage.count(), 0);
}

} // namespace 