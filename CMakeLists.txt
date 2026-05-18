cmake_minimum_required(VERSION 3.10)
project(print)
set(PRINT_VERSION_MAJOR 0)
set(PRINT_VERSION_MINOR 1)
set(PRINT_VERSION_PATCH 0)
set(PRINT_VERSION_TWEAK 0)
set(PRINT_VERSION ${PRINT_VERSION_MAJOR}.${PRINT_VERSION_MINOR}.${PRINT_VERSION_PATCH}.${PRINT_VERSION_TWEAK})
set(PRINT_VERSION_STRING "v${PRINT_VERSION}")

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(BUILD_TESTS "Build tests" ON)

if(MSVC)
    set(gtest_force_shared_crt ON CACHE BOOL "Use shared runtime" FORCE)
    add_compile_options(/EHsc /MD)
endif()

add_subdirectory(banking)

if(BUILD_TESTS)
    enable_testing()
    add_subdirectory(third-party/gtest ${CMAKE_BINARY_DIR}/gtest)
    add_executable(banking_check tests/test_account.cpp tests/test_transaction.cpp tests/test_transaction_mock.cpp)
    target_link_libraries(banking_check banking gtest_main gmock)
    target_include_directories(banking_check PRIVATE banking)
    if(MSVC)
        set_target_properties(banking_check PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        )
        set_target_properties(gtest PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        )
        set_target_properties(gtest_main PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        )
        set_target_properties(gmock PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        )
        set_target_properties(gmock_main PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        )
        set_target_properties(banking PROPERTIES
            MSVC_RUNTIME_LIBRARY "MultiThreadedDLL"
        )
    endif()
    add_test(NAME banking_check COMMAND banking_check)
endif()

include(CPackConfig.cmake)

add_executable(solver solver.cpp)
install(TARGETS solver RUNTIME DESTINATION bin)
