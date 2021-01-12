/**
 * Copyright 2020 Iosif Haidu - All rights reserved.
 */

#include "gtest/gtest.h"
#include "modules/gui/opengl.h"
#include "bindings/rebol2/cpp/default.h"
#include "internal/errors/errors.h"

#ifndef OS_MACOS
#include <filesystem>
#endif
#include <iostream>

#define GTEST_COUT std::cerr << "[          ] [ INFO ]"

namespace
{

using namespace std::chrono_literals;

class TestsOpenGL : public ::testing::Test
{
protected:

    void SetUp() override
    {
    }
    void TearDown() override
    {
    }

    GUI::OpenGL opengl;
};

TEST_F(TestsOpenGL, StartMainThread) {
    auto onLoad = [=](){
        std::this_thread::sleep_for(1s);
        opengl.stop();
    };
    opengl.init(false);
    {
        opengl.createMainWindow("Main thread window", 50, 50, 800, 600, 0xFF0000, true);
        std::future<void> done = std::async(std::launch::async, onLoad);
        ASSERT_TRUE(opengl.start());
        done.wait();
    }
    opengl.init(false);
    {
        opengl.createMainWindow("Another main thread window", 10, 40, 600, 400, 0xFFFF00, true);
        std::future<void> done = std::async(std::launch::async, onLoad);
        ASSERT_TRUE(opengl.start());
        done.wait();
    }
}

#ifndef OS_MACOS    // OSX does not support handling glfw main loop in different thread
TEST_F(TestsOpenGL, StartThread) {
    opengl.init(true);
    ASSERT_TRUE(opengl.start());
    int res = opengl.createMainWindow("Background thread window", 150, 150, 500, 300, 0x0000FF, true);
    ASSERT_NE(res, ERR_GUI_INVALID_WIDGET);
    std::this_thread::sleep_for(1s);
    opengl.stop();

    opengl.init(true);
    ASSERT_TRUE(opengl.start());
    res = opengl.createMainWindow("Another background thread window", 200, 200, 600, 200, 0x00FF00, true);
    ASSERT_NE(res, ERR_GUI_INVALID_WIDGET);
    std::this_thread::sleep_for(1s);
    opengl.stop();
}
#endif

#ifndef OS_MACOS    // missing filesystem
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
#endif

}