cmake_minimum_required(VERSION 3.27)
project(2dGame)

set(CMAKE_CXX_STANDARD 20)

set(BUILD_SHARED_LIBS FALSE)

## Enable AddressSanitizer to keep track of memory leaks
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fsanitize=address -g")

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
        zombie.cpp
        zombie.hpp
        character.cpp
        character.hpp
        dataFileEnum.hpp
        firstEnemy.cpp
        firstEnemy.hpp
        bullet.cpp
        bullet.hpp
        movementEnum.hpp
        robot.hpp
        robot.cpp
        enemy.cpp
        enemy.hpp
        robotBullet.cpp
        robotBullet.hpp
        game.cpp
        game.hpp
        knife.cpp
        knife.hpp

)
target_link_libraries(2dGame fmt sfml-graphics)
