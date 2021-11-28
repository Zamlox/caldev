cmake_minimum_required(VERSION 3.20)
project(caldev VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(cmake/functions.cmake)

# Configure version number
configure_file(src/caldev.h.in caldev.h)
include_directories(${PROJECT_BINARY_DIR})
include_directories(src)
include_directories(src/extern/glfw/include)
include_directories(src/extern/GSL/include)
include_directories(src/extern/imgui/examples)
include_directories(src/extern/imgui)
include_directories(src/extern/rebsdev/src/include)
include_directories(src/extern/rebsdev/src/glue)
include_directories(src/extern/googletest/googletest/include)

# get build type
get_build_type(${CMAKE_BINARY_DIR} BUILD_TYPE)
get_platform_type(${CMAKE_BINARY_DIR} IS_32)

# caldev targets name
set(TEST_ALL test_all)
if(IS_32 STREQUAL "32")
    # 32 bits
    set(CALDEV_STATIC caldev32static)
    set(CALDEV_SHARED caldev32)

    # rebol demo for 32 bit
    add_custom_target(rebol_demo)
    add_custom_command(
            TARGET rebol_demo
            COMMAND rebol -sqv ${CMAKE_SOURCE_DIR}\\src\\tests\\bindings\\rebol2\\test-gui.r ${CMAKE_BINARY_DIR}
    )
else()
    # 64 bits
    set(CALDEV_STATIC caldevstatic)
    set(CALDEV_SHARED caldev)
endif()

# caldev library target
add_library(${CALDEV_STATIC} STATIC)
add_library(${CALDEV_SHARED} SHARED)
# tests targets
add_executable(${TEST_ALL})

if(IS_32 STREQUAL "32")
    set_property(
            TARGET ${CALDEV_SHARED} ${CALDEV_STATIC} ${TEST_ALL}
            APPEND PROPERTY COMPILE_FLAGS "-m32"
    )
    set_property(
            TARGET ${CALDEV_SHARED} ${CALDEV_STATIC} ${TEST_ALL}
            APPEND PROPERTY LINK_FLAGS "-m32"
    )
endif()

#target_link_libraries(${CALDEV_SHARED} PUBLIC ${GLFW_LIB_OUTPUT}\\glfw3.lib opengl32.lib)

# defines
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_compile_definitions(OS_WINDOWS=1)
    set(OPENGL opengl32.lib)
    set(GLFW_LIB_OUTPUT "${CMAKE_BINARY_DIR}/src/extern/glfw/src/${BUILD_TYPE}")
    set(GLFW_LIB ${GLFW_LIB_OUTPUT}\\glfw3.lib)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_compile_definitions(OS_LINUX=1)
    set(OPENGL GL)
    set(GLFW_LIB_OUTPUT "${CMAKE_BINARY_DIR}/src/extern/glfw/src")
    set(GLFW_LIB ${GLFW_LIB_OUTPUT}/glfw3.lib)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_compile_definitions(OS_MACOS=1)
    set(OPENGL "")
    set(GLFW_LIB_OUTPUT "${CMAKE_BINARY_DIR}/src/extern/glfw/src")
    set(GLFW_LIB ${GLFW_LIB_OUTPUT}/glfw3.lib)
endif()
add_compile_definitions(CALDEV_EXPORT=1)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION=1)

# subfolders
add_subdirectory(src/api)
add_subdirectory(src/internal)
add_subdirectory(src/modules)
add_subdirectory(src/extern/glfw)
add_subdirectory(src/extern/googletest)
add_subdirectory(src/extern/GSL)
add_subdirectory(src/extern/imgui)
#add_subdirectory(src/extern/stb)
add_subdirectory(src/extern/rebsdev)
add_subdirectory(src/tests)


# caldev dependencies
add_dependencies(${CALDEV_SHARED} glfw gmock_main)
add_dependencies(${CALDEV_STATIC} glfw gmock_main)
add_dependencies(${TEST_ALL} ${CALDEV_STATIC})

# additional compiler options
target_link_options(${CALDEV_SHARED} PUBLIC ${REBSDEV_LIB_OPTIONS})
target_link_libraries(${CALDEV_SHARED} PUBLIC
        ${REBSDEV_LIBS}
        glfw
        ${OPENGL}
        )

# all libs for static linking
set(LIBS_ALL_STATIC
        ${CALDEV_STATIC}
        ${REBSDEV_LIBS}
        glfw
        ${OPENGL}
        gmock_main
        )

# test linking libraries
target_link_libraries(${TEST_ALL} PUBLIC ${LIBS_ALL_STATIC})
