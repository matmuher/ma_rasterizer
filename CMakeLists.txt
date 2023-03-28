cmake_minimum_required(VERSION 3.5)
project(MaRasterizer VERSION 0.1)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic -g)

add_library(MaRasterizerLib src/MaRasterizer.cpp src/Debug.cpp)
target_link_libraries(MaRasterizerLib sfml-graphics sfml-window sfml-system)
target_include_directories(MaRasterizerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

add_executable(MaApp src/main.cpp)
target_link_libraries(MaApp MaRasterizerLib)

install(TARGETS MaApp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)