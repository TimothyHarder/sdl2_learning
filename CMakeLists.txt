cmake_minimum_required(VERSION 3.24)
project(sdl2_learning)

set(CMAKE_CXX_STANDARD 23)

set(SDL2_INCLUDE_DIR C:/Users/timot/CLionProjects/cpp_libs/SDL/include)
set(SDL2_LIB_DIR C:/Users/timot/CLionProjects/cpp_libs/SDL/lib/x64)

include_directories(${SDL2_INCLUDE_DIR})
link_directories(${SDL2_LIB_DIR})

add_executable(sdl2_learning 04/main.cpp)

target_link_libraries(${PROJECT_NAME} SDL2main SDL2)