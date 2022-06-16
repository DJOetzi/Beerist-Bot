cmake_minimum_required(VERSION 3.22)
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Beerist7 VERSION 7.0 DESCRIPTION "seventh iteration of the Beerist Bot")

add_subdirectory(libs/DPP)
add_subdirectory(libs/spdlog)

add_executable(${PROJECT_NAME} src/main.cpp src/utils/fileutils.cpp src/utils/fileutils.h)

target_link_libraries(${PROJECT_NAME}
        dpp
        spdlog
)
target_include_directories(${PROJECT_NAME} PRIVATE
        libs/DPP/include
        libs/spdlog/include
)