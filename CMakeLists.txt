cmake_minimum_required(VERSION 3.27)
project(2dGame)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

include(FetchContent)

FetchContent_Declare(
        fmt
        GIT_REPOSITORY https://github.com/fmtlib/fmt.git
        GIT_TAG 10.2.1
)

FetchContent_Declare(
        SFML
        GIT_REPOSITORY https://github.com/SFML/SFML.git
        GIT_TAG 2.6.1
)

FetchContent_MakeAvailable(fmt)
FetchContent_MakeAvailable(SFML)

add_executable(2dGame main.cpp
        hero.hpp
        hero.cpp
        utilities.hpp
        utilities.cpp
        mainMenu.hpp
        mainMenu.cpp

        )
target_link_libraries(2dGame fmt sfml-graphics)
