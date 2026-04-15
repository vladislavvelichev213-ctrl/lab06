cmake_minimum_required(VERSION 3.10)
project(banking)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_library(banking STATIC Account.cpp Transaction.cpp)

target_include_directories(banking PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})

if(BUILD_TESTS)
    enable_testing()
    
    # Add Google Test
    add_subdirectory(../third-party/gtest ${CMAKE_BINARY_DIR}/gtest)
    
    # Test files
    file(GLOB BANKING_TEST_SOURCES tests/*.cpp)
    add_executable(banking_check ${BANKING_TEST_SOURCES})
    
    target_link_libraries(banking_check banking gtest_main)
    target_include_directories(banking_check PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})
    
    add_test(NAME banking_check COMMAND banking_check)
endif()

# Coverage
option(ENABLE_COVERAGE "Enable coverage" OFF)
if(ENABLE_COVERAGE)
    target_compile_options(banking PRIVATE --coverage)
    target_link_options(banking PRIVATE --coverage)
endif()
