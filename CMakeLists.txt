cmake_minimum_required(VERSION 3.15)

project(compilators)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_EXE_LINKER_FLAGS "-static")

include(FetchContent)

FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
)

set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

FetchContent_MakeAvailable(googletest)

add_executable(
    roman-numbers-cli
    src/roman-numbers-cli.cpp
    src/roman-numbers.cpp
    src/automaton.cpp
    src/alphabet.cpp
)

add_executable(
    eval-arith-cli
    src/arithmetic.cpp
    src/numeric-expresions.cpp
    src/automaton.cpp
    src/alphabet.cpp
)

target_include_directories(
    roman-numbers-cli PRIVATE include
)

target_include_directories(
    eval-arith-cli PRIVATE include
)

add_executable(
    numeric-expresions-cli
    src/numeric-expresions-cli.cpp
    src/numeric-expresions.cpp
    src/automaton.cpp
    src/alphabet.cpp
)

target_include_directories(
    numeric-expresions-cli PRIVATE include
)

## tests
enable_testing()


add_executable(
    roman-numbers-test
    test/roman-numbers-test.cpp
    src/roman-numbers.cpp
    src/automaton.cpp
    src/alphabet.cpp
)


target_compile_definitions(roman-numbers-test PRIVATE 
    RESOURCES_PATH="${CMAKE_CURRENT_SOURCE_DIR}/resources/"
)
target_include_directories(roman-numbers-test PUBLIC include)
target_link_libraries(roman-numbers-test PUBLIC GTest::gtest_main)

add_executable(
    numeric-expresions-test
    test/numeric-expresions-test.cpp
    src/numeric-expresions.cpp
    src/automaton.cpp
    src/alphabet.cpp
)

add_executable(
    alphabet-test
    test/alphabet-test.cpp
    src/alphabet.cpp
)
    
target_include_directories(numeric-expresions-test PUBLIC include)
target_link_libraries(numeric-expresions-test PUBLIC GTest::gtest_main)

target_include_directories(alphabet-test PUBLIC include)
target_link_libraries(alphabet-test PUBLIC GTest::gtest_main)

include(GoogleTest)
gtest_discover_tests(roman-numbers-test)
