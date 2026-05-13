cmake_minimum_required(VERSION 3.26)

project(EngineCalc LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(Threads REQUIRED)

file(GLOB_RECURSE MAIN_SOURCES CONFIGURE_DEPENDS "src/*.cc")
list(REMOVE_ITEM MAIN_SOURCES "${CMAKE_CURRENT_SOURCE_DIR}/src/main.cc")

add_library(Main STATIC ${MAIN_SOURCES})
target_include_directories(Main PUBLIC src)
target_compile_options(Main PRIVATE -Wall)
target_link_libraries(Main PUBLIC Threads::Threads)

add_executable(engineCalc src/main.cc)
target_compile_options(engineCalc PRIVATE -Wall)
target_link_libraries(engineCalc PRIVATE Main)

option(ENGINECALC_BUILD_TESTS "Build the EngineCalc test suite" ON)

if(ENGINECALC_BUILD_TESTS)
    include(FetchContent)
    FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG v1.14.0
    )
    set(INSTALL_GTEST OFF CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)

    enable_testing()

    file(GLOB_RECURSE TEST_SOURCES CONFIGURE_DEPENDS "test/*_test.cc")

    add_executable(testRunner ${TEST_SOURCES} test/test_runner.cc)
    target_compile_options(testRunner PRIVATE -Wall)
    target_link_libraries(testRunner PRIVATE Main GTest::gtest)

    include(GoogleTest)
    gtest_discover_tests(testRunner)
endif()
