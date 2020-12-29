/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "modules/gui/opengl.h"
#include "internal/os/util.h"
#include "bindings/rebol2/cpp/default.h"


#include <filesystem>
#include <iostream>

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

namespace
{

class TestsOpenGL : public ::testing::Test
{
protected:

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    static void* onLoad(void* pParamP)
    {
        GUI::OpenGL* pOpenGL = static_cast<GUI::OpenGL*>(pParamP);
        if (pOpenGL)
        {
            int res = pOpenGL->createMainWindow("Main thread window", 50, 50, 800, 600, 0xFF0000, true);
        }
        threadM.start();
        return nullptr;
    }

    static void* onLoad1(void* pParamP)
    {
        GUI::OpenGL* pOpenGL = static_cast<GUI::OpenGL*>(pParamP);
        if (pOpenGL)
        {
            int res = pOpenGL->createMainWindow("Another main thread window", 10, 40, 600, 400, 0xFFFF00, true);
        }
        threadM.start();
        return nullptr;
    }

    static void* stopMainThread(void* pParamP)
    {
        GUI::OpenGL* pOpenGL = static_cast<GUI::OpenGL*>(pParamP);
        if (pOpenGL)
        {
            Os::Util::instance().msleep(1000);
            pOpenGL->stop();
        }
        return nullptr;
    }

    static GUI::OpenGL opengl;
    static Os::Thread threadM;
};

GUI::OpenGL TestsOpenGL::opengl;
Os::Thread TestsOpenGL::threadM{"TestsOpenGL", nullptr, &TestsOpenGL::stopMainThread, &TestsOpenGL::opengl};


TEST_F(TestsOpenGL, StartMainThread) {
    ASSERT_TRUE(opengl.startOnMainThread(&TestsOpenGL::onLoad));
    ASSERT_TRUE(opengl.startOnMainThread(&TestsOpenGL::onLoad1));
}

#ifndef OS_MACOS    // OSX does not support handling glfw main loop in different thread
TEST_F(TestsOpenGL, StartThread) {
    ASSERT_TRUE(opengl.startOnThread());
    int res = opengl.createMainWindow("Background thread window", 150, 150, 500, 300, 0x0000FF, true);
    ASSERT_NE(res, GUI::INVALID_WIDGET_ID);
    Os::Util::instance().msleep(1000);
    opengl.closeMainWindow();

    ASSERT_TRUE(opengl.startOnThread());
    res = opengl.createMainWindow("Another background thread window", 200, 200, 600, 200, 0x00FF00, true);
    ASSERT_NE(res, GUI::INVALID_WIDGET_ID);
    Os::Util::instance().msleep(1000);
    opengl.closeMainWindow();
}
#endif

TEST_F(TestsOpenGL, CreateFont) {
    std::filesystem::path cwd = std::filesystem::current_path();
#ifdef OS_WINDOWS
    cwd.append("extern\\imgui\\misc\\fonts\\DroidSans.ttf");
#else
    cwd.append("extern/imgui/misc/fonts/DroidSans.ttf");
#endif
    Bind::Rebol2::Default::instance().setFaceFont(
        "TestFont1",
        10,
        "Regular",
        {100, 100, 100},
        "Left",
        "Top",
        {10, 20},
        {21, 22},
        {13,14},
        cwd.string()
    );
    GUI::Font* pFont = opengl.createFont(Bind::Rebol2::Default::instance().getFont());
    ASSERT_NE(pFont, nullptr);
    GUI::Font* pFont1 = opengl.createFont(Bind::Rebol2::Default::instance().getFont());
    ASSERT_EQ(pFont, pFont1);
}

}