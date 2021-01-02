/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "api/api.h"
#include "api/imp/apiimp.h"

namespace {

TEST(APITest, Initialization){
    EXPECT_EQ(initGUI(Api::GUI_OPENGL2), 0);
    EXPECT_EQ(stopGUI(), 0);
    EXPECT_EQ(initGUI(Api::GUI_DIRECTX), 0);
    EXPECT_NE(initGUI(99), 0);
}

TEST(APITest, CreateMainWindow) {
    initGUI(Api::GUI_OPENGL2);
    EXPECT_NE(createMainWindow("Dummy", 30, 30, 100, 100, 0xF0F0F0, false), 0);
    stopGUI();
    EXPECT_EQ(createMainWindow("Dummy", 30, 30, 100, 100, 0xF0F0F0, false), Api::ERROR_API_NOT_INITIALIZED);
}

} // anonymous namespace