cmake_minimum_required(VERSION 3.5.0)
project(emulator VERSION 0.1.0 LANGUAGES C CXX)

find_package(SDL2 REQUIRED)

include_directories(imgui include)

file(GLOB IMGUI_SOURCES imgui/*.cpp)
file(GLOB PROJECT_SOURCES source/*.cpp)
set(SOURCES ${PROJECT_SOURCES} ${IMGUI_SOURCES})

add_executable(emulator ${SOURCES})
target_link_libraries(emulator ${SDL2_LIBRARIES})
target_compile_features(emulator PRIVATE cxx_std_17)
