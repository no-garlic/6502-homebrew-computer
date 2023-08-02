cmake_minimum_required(VERSION 3.5.0)
project(vcpkg_test VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

set(SOURCES source/main.cpp)

add_executable(vcpkg_test ${SOURCES})
target_link_libraries(vcpkg_test ${SDL2_LIBRARIES})
