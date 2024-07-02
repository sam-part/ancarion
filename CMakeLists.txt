cmake_minimum_required(VERSION 3.28)
project(ancarion)

set(CMAKE_CXX_STANDARD 20)

add_executable(ancarion src/main.cpp
        src/engine/types/size.h
        src/engine/types/size.cpp
        src/engine/types/color.h
        src/engine/types/glyph.h
)

find_package(SFML COMPONENTS system window graphics CONFIG REQUIRED)
target_link_libraries(ancarion PRIVATE sfml-system sfml-graphics sfml-window)