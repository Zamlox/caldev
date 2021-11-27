set(SOURCE_TEST_API
        api/test_api.cpp
        )

set(SOURCE_TEST_REBSDEV
        external/rebsdev/test_deep_eval.cpp
        )

set(SOURCE_TEST_GUI
        internal/gui/test_opengl.cpp
        )

set(SOURCE_TEST_OS
        internal/os/test_sync.cpp
        )

set(SOURCE_TEST_ALL
        ${SOURCE_TEST_API}
        ${SOURCE_TEST_REBSDEV}
        ${SOURCE_TEST_GUI}
        ${SOURCE_TEST_OS}
        )

target_sources(${TEST_ALL} PRIVATE ${SOURCE_TEST_ALL})