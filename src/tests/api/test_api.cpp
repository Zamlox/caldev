/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "rebol2.h"

namespace {

TEST(RebolAPITest, Initialization){
    EXPECT_EQ(rebInitGUI(0), 0);
}

} // anonymous namespace