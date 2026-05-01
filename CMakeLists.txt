cmake_minimum_required(VERSION 3.10)
project(lab05)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest ${CMAKE_BINARY_DIR}/gtest)
    add_executable(banking_check tests/test_account.cpp tests/test_transaction.cpp tests/test_transaction_mock.cpp)
    target_link_libraries(banking_check banking gtest_main gmock)
    target_include_directories(banking_check PRIVATE banking)
    add_test(NAME banking_check COMMAND banking_check)
endif()
