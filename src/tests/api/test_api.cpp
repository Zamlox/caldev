/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "api/api.h"
#include "api/imp/apiimp.h"
#include "internal/os/util.h"

namespace {

TEST(APITest, Initialization){
    EXPECT_EQ(initGUI(Api::GUI_OPENGL2), 0);
    EXPECT_EQ(stopGUI(), 0);
    EXPECT_EQ(initGUI(Api::GUI_DIRECTX), 0);
    stopGUI();
    EXPECT_NE(initGUI(99), 0);
    stopGUI();
}

TEST(APITest, CreateMainWindow) {
    initGUI(Api::GUI_OPENGL2);
    EXPECT_NE(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), 0);
    stopGUI();
    EXPECT_EQ(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), Api::ERROR_API_NOT_INITIALIZED);
    stopGUI();
}

TEST(APITest, HideMainWindow) {
    initGUI(Api::GUI_OPENGL2);
    EXPECT_NE(createMainWindow("Test HideMainWindow", 30, 30, 400, 100, 0xF0F0F0, true), 0);
    Os::Util::instance().msleep(1000);
    hideMainWindow();
    Os::Util::instance().msleep(1000);
    stopGUI();
}

TEST(APITest, ShowMainWindow) {
    initGUI(Api::GUI_OPENGL2);
    EXPECT_NE(createMainWindow("Test ShowMainWindow", 30, 30, 400, 100, 0xF0F0F0, true), 0);
    Os::Util::instance().msleep(1000);
    hideMainWindow();
    Os::Util::instance().msleep(1000);
    showMainWindow();
    Os::Util::instance().msleep(1000);
    stopGUI();
}

} // anonymous namespace