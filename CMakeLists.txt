cmake_minimum_required(VERSION 3.2)
project(LearnOpenGl)

set(CMAKE_CXX_STANDARD 20)

add_executable(learnOpenGlExe
  src/main.cpp
  src/glad.c
  src/shared.cpp)
include_directories(./src)
include_directories(./include)
target_link_libraries(learnOpenGlExe glfw)
