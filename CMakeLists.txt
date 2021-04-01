cmake_minimum_required(VERSION 3.0)
project(StringBeat C)

set(CMAKE_C_STANDARD 99)

# Setting parameters for raylib
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE) # don't build the supplied examples
set(BUILD_GAMES    OFF CACHE BOOL "" FORCE) # or games

add_subdirectory(libs/raylib)

add_executable(StringBeat src/main.c src/commandinterpret.c src/animstates.c src/utils.c)
target_link_libraries(StringBeat PRIVATE raylib)