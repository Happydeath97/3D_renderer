cmake_minimum_required(VERSION 3.20)
project(math_visualizer)

set(CMAKE_CXX_STANDARD 20)

# Add raylib to build
add_subdirectory(extern/raylib)

# Include raylib headers
include_directories(extern/raylib/src)

# Add your main app
add_executable(3D_renderer main.cpp
        math/Vec3.h)

# Link your app with raylib and required Windows system libs
target_link_libraries(3D_renderer
        raylib
        opengl32
        gdi32
        winmm
        shell32
)
