cmake_minimum_required(VERSION 3.30)
project(SpaceInvaderRaylib)

set(CMAKE_CXX_STANDARD 20)

# Download Raylib
include(FetchContent)
FetchContent_Declare(raylib GIT_REPOSITORY "https://github.com/raysan5/raylib.git")
FetchContent_MakeAvailable(raylib)


# add_executable(SpaceInvaderRaylib main.cpp)



add_executable(${PROJECT_NAME} main.cpp
        Game.cpp
        Game.h
        GameWindow.h
        Projectile.cpp
        Projectile.h
        Entity.cpp
        Entity.h
        ECS_Component.cpp
        ECS_Component.h
        Player.cpp
        Player.h
        ECS_Entity.cpp
        ECS_Entity.h
        ECS_System.cpp
        ECS_System.h
)


target_link_libraries(${PROJECT_NAME} raylib)
set_target_properties(${PROJECT_NAME} PROPERTIES RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_CURRENT_SOURCE_DIR})


