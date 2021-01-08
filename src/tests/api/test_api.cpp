/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "api/api.h"
#include "api/imp/apiimp.h"
#include "internal/os/util.h"

namespace {

TEST(APITest, Initialization){
    EXPECT_EQ(guiEngineInit(static_cast<int>(Api::GuiType::GUI_OPENGL2)), 0);
    EXPECT_EQ(guiEngineStop(), 0);
    EXPECT_EQ(guiEngineInit(static_cast<int>(Api::GuiType::GUI_DIRECTX)), 0);
    guiEngineStop();
    EXPECT_NE(guiEngineInit(99), 0);
    guiEngineStop();
}

TEST(APITest, CreateMainWindow) {
    guiEngineInit(static_cast<int>(Api::GuiType::GUI_OPENGL2));
    EXPECT_NE(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), 0);
    guiEngineStop();
    EXPECT_EQ(createMainWindow("Test CreateMainWindow", 30, 30, 400, 100, 0xF0F0F0, false), Api::ERROR_API_NOT_INITIALIZED);
    guiEngineStop();
}

TEST(APITest, HideMainWindow) {
#ifndef OS_MACOS
    guiEngineInit(static_cast<int>(Api::GuiType::GUI_OPENGL2));
    guiEngineStart(static_cast<int>(Api::GuiEngineExecutionType::BKG_THREAD));
    EXPECT_NE(createMainWindow("Test HideMainWindow", 30, 30, 400, 100, 0xF0F0F0, true), 0);
    Os::Util::instance().msleep(1000);
    hideMainWindow();
    Os::Util::instance().msleep(1000);
    guiEngineStop();
#endif
}

TEST(APITest, ShowMainWindow) {
#ifndef OS_MACOS
    guiEngineInit(static_cast<int>(Api::GuiType::GUI_OPENGL2));
    guiEngineStart(static_cast<int>(Api::GuiEngineExecutionType::BKG_THREAD));
    EXPECT_NE(createMainWindow("Test ShowMainWindow", 30, 30, 400, 100, 0xF0F0F0, true), 0);
    Os::Util::instance().msleep(1000);
    hideMainWindow();
    Os::Util::instance().msleep(1000);
    showMainWindow();
    Os::Util::instance().msleep(1000);
    guiEngineStop();
#endif
}

} // anonymous namespace