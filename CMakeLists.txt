cmake_minimum_required(VERSION 3.20)
project(caldev VERSION 0.1)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include(CMake/functions.cmake)

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

# get build type
get_build_type(${CMAKE_BINARY_DIR} BUILD_TYPE)
set(GLFW_LIB_OUTPUT "${CMAKE_BINARY_DIR}/src/extern/glfw/src/${BUILD_TYPE}")

# caldev targets name
if(CMAKE_SIZEOF_VOID_P EQUAL 8)
    # 64 bits
    set(CALDEV_STATIC caldevstatic)
    set(CALDEV_SHARED caldev)
elseif(CMAKE_SIZEOF_VOID_P EQUAL 4)
    # 32 bits
    set(CALDEV_STATIC caldev32static)
    set(CALDEV_SHARED caldev32)
    # rebol demo for 32 bit
    add_custom_target(rebol_demo)
    add_custom_command(
            TARGET rebol_demo
            COMMAND rebol -sqv ${CMAKE_SOURCE_DIR}\\src\\tests\\bindings\\rebol2\\test-gui.r ${CMAKE_BINARY_DIR}
    )
endif()

# defines
if(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_compile_definitions(OS_WINDOWS=1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Linux")
    add_compile_definitions(OS_LINUX=1)
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    add_compile_definitions(OS_MACOS=1)
endif()
add_compile_definitions(CALDEV_EXPORT=1)
add_compile_definitions(STB_IMAGE_IMPLEMENTATION=1)


# caldev library target 64bit
add_library(${CALDEV_STATIC} STATIC)
add_library(${CALDEV_SHARED} SHARED)

target_link_libraries(${CALDEV_SHARED} PUBLIC ${GLFW_LIB_OUTPUT}\\glfw3.lib opengl32.lib)


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

# caldev dependencies
add_dependencies(${CALDEV_SHARED} glfw)
add_dependencies(${CALDEV_STATIC} glfw)

# additional compiler options
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${REBSDEV_COMPILE_OPTIONS}")
target_link_options(${CALDEV_SHARED} PUBLIC ${REBSDEV_LIB_OPTIONS})
target_link_libraries(${CALDEV_SHARED} PUBLIC ${REBSDEV_LIBS})
