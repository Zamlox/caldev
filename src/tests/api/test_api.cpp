/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "api/api.h"
#include "api/imp/apiimp.h"

namespace {

TEST(RebolAPITest, Initialization){
    EXPECT_EQ(initGUI(Api::GUI_OPENGL2), 0);
    EXPECT_EQ(stopGUI(), 0);
    EXPECT_EQ(initGUI(Api::GUI_DIRECTX), 0);
    EXPECT_NE(initGUI(99), 0);
}

} // anonymous namespace