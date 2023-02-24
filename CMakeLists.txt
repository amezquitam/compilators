cmake_minimum_required(VERSION 3.15)

project(compilators)

set(CMAKE_CXX_STANDARD 20)

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)



add_executable(
    languaje
    src/languaje.cpp
)


add_executable(
    roman-numbers
    src/roman-numbers.cpp
    src/cli.cpp
)

target_include_directories(roman-numbers PUBLIC include)


enable_testing()


add_executable(
    alphabet-test
    test/alphabet-test.cpp)

target_include_directories(alphabet-test PUBLIC include)
target_link_libraries(alphabet-test PUBLIC GTest::gtest_main)


add_executable(
    roman-numbers-test
    test/roman-numbers-test.cpp)

target_include_directories(roman-numbers-test PUBLIC include)
target_link_libraries(roman-numbers-test PUBLIC GTest::gtest_main)


include(GoogleTest)
gtest_discover_tests(alphabet-test)
gtest_discover_tests(roman-numbers-test)
