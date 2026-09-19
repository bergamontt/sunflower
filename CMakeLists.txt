cmake_minimum_required(VERSION 3.20)

project(
    sunflower
    VERSION 0.1.0
    DESCRIPTION "A cross-platform screen time limiter tool"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED on)

find_package(Qt6 REQUIRED COMPONENTS Core Widgets Sql)

qt_standard_project_setup()

add_subdirectory(src)