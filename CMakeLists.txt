cmake_minimum_required(VERSION 3.2)
project(LearnOpenGl)

add_executable(learnOpenGlExe
  src/main.cpp
  src/glad.c
  src/shared.cpp
  src/shader.cpp
  src/file.cpp
)

target_compile_features(learnOpenGlExe PUBLIC cxx_std_20)

include_directories(./src)
include_directories(./include)
target_link_libraries(learnOpenGlExe glfw fmt)


# testing

configure_file(test/simple.txt
  test/simple.txt
  COPYONLY
)

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)
FetchContent_MakeAvailable(googletest)

enable_testing()

add_executable(
  file_test
  src/file_test.cpp
  src/file.cpp
)
target_link_libraries(
  file_test
  GTest::gtest_main
  fmt
)

include(GoogleTest)
gtest_discover_tests(file_test)
