cmake_minimum_required(VERSION 3.20)

project(LimitLit VERSION 0.6.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(PkgConfig REQUIRED)
pkg_check_modules(SDL2 REQUIRED sdl2)

add_executable(LimitLit
    src/main.cpp
    src/Application.cpp
    src/Window.cpp
    src/Renderer.cpp

    engine/graphics/Framebuffer.cpp
    engine/graphics/BitmapFont.cpp

    engine/math/Vec3.cpp
    engine/render/RayTracer.cpp

    ui/ClassicUI.cpp
)

target_include_directories(LimitLit PRIVATE
    include
    ${SDL2_INCLUDE_DIRS}
)

target_link_directories(LimitLit PRIVATE
    ${SDL2_LIBRARY_DIRS}
)

target_link_libraries(LimitLit PRIVATE
    ${SDL2_LIBRARIES}
)

target_compile_options(LimitLit PRIVATE
    -Wall
    -Wextra
    -Wpedantic
)
