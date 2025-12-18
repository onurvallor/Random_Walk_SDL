
cmake_minimum_required(VERSION 3.20)

project(Random_Walk_SDL VERSION 0.1.0 LANGUAGES CXX)

add_executable(${PROJECT_NAME}
  src/main.cpp
)

target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)

find_package(SDL3 REQUIRED CONFIG)

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)
