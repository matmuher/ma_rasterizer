cmake_minimum_required(VERSION 3.5)
project(MaRasterizer VERSION 0.1)

find_package(SFML 2.5 COMPONENTS system window graphics REQUIRED)

add_compile_options(-Wall -Wextra -Wpedantic -g -std=c++2a)

add_library(MaRasterizerLib
            src/MaRasterizer.cpp
            src/Debug.cpp
            src/DrawingAlgos.cpp
            src/CoordsTransform.cpp
            src/Interpolation.cpp
            src/Model.cpp
            src/Camera.cpp
            src/Updater.cpp
            src/Clipping.cpp
            src/LinearAlgebra.cpp
            src/Geometry.cpp
            src/SceneManage.cpp)

target_link_libraries(MaRasterizerLib sfml-graphics sfml-window sfml-system)
target_include_directories(MaRasterizerLib PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)

find_package (Eigen3 3.3 REQUIRED NO_MODULE)
include_directories(${EIGEN3_INCLUDE_DIR})

add_executable(MaApp src/main.cpp)
target_link_libraries(MaApp MaRasterizerLib)
target_link_libraries(MaApp Eigen3::Eigen)

install(TARGETS MaApp DESTINATION ${CMAKE_CURRENT_SOURCE_DIR}/bin)