/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "rebol2.h"
#include "rebol2imp.h"

namespace {

TEST(RebolAPITest, Initialization){
    EXPECT_EQ(rebInitGUI(Api::GUI_OPENGL2), 0);
    EXPECT_EQ(rebInitGUI(Api::GUI_DIRECTX), 0);
    EXPECT_NE(rebInitGUI(99), 0);
}

} // anonymous namespace