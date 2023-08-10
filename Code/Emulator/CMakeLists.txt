cmake_minimum_required(VERSION 3.5.0)
project(vcpkg_test VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

include_directories(imgui)

file(GLOB IMGUI_SOURCES imgui/*.cpp)
file(GLOB PROJECT_SOURCES source/*.cpp)
set(SOURCES ${PROJECT_SOURCES} ${IMGUI_SOURCES})
#set(SOURCES source/main.cpp ${IMGUI_SOURCES})

add_executable(vcpkg_test ${SOURCES})
target_link_libraries(vcpkg_test ${SDL2_LIBRARIES})
target_compile_features(vcpkg_test PRIVATE cxx_std_17)
