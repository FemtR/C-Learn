cmake_minimum_required(VERSION 3.16)

project(CLearn LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

include(CTest)

function(apply_common_warnings target)
    target_compile_options(${target} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endfunction()

function(add_lab_executable target source)
    add_executable(${target} ${source})
    apply_common_warnings(${target})
endfunction()

# Week 01 / Day 01: compile, link, run, and warning awareness.
set(W01D01_DIR ${CMAKE_CURRENT_SOURCE_DIR}/labs/w01/d01_compile_flow)
set(W01D01_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/labs/w01/d01_compile_flow)

add_lab_executable(w01d01_warning_fixed
    ${W01D01_DIR}/warning_fixed.cpp
)

add_lab_executable(w01d01_runtime_error
    ${W01D01_DIR}/runtime_error.cpp
)

add_lab_executable(w01d01_check_task
    ${W01D01_DIR}/check_task.cpp
)

add_test(NAME w01d01_check_task_runs COMMAND w01d01_check_task) 

add_test(NAME w01d01_warning_fixed_runs COMMAND w01d01_warning_fixed)

add_custom_target(w01d01_preprocess
    COMMAND ${CMAKE_COMMAND} -E make_directory ${W01D01_BUILD_DIR}
    COMMAND ${CMAKE_CXX_COMPILER}
            -std=c++17
            -E
            ${W01D01_DIR}/warning_fixed.cpp
            -o ${W01D01_BUILD_DIR}/warning_fixed.i
    COMMAND wc -l ${W01D01_BUILD_DIR}/warning_fixed.i
    COMMENT "Preprocess Day1 warning_fixed.cpp and count expanded lines"
    VERBATIM
)

add_custom_target(w01d01_warning_bad_check
    COMMAND ${CMAKE_CXX_COMPILER}
            -std=c++17
            -Wall
            -Wextra
            -Wpedantic
            ${W01D01_DIR}/warning_bad.cpp
            -o ${W01D01_BUILD_DIR}/warning_bad
    COMMENT "Compile Day1 warning_bad.cpp to observe compiler warnings"
    VERBATIM
)

add_custom_target(w01d01_link_error_check
    COMMAND ${CMAKE_COMMAND} -E make_directory ${W01D01_BUILD_DIR}
    COMMAND bash -c
            "if '${CMAKE_CXX_COMPILER}' -std=c++17 -Wall -Wextra -Wpedantic '${W01D01_DIR}/link_error.cpp' -o '${W01D01_BUILD_DIR}/link_error'; then echo 'expected link failure, but build succeeded'; exit 1; else echo 'observed expected link failure'; fi"
    COMMENT "Build Day1 link_error.cpp and confirm the expected undefined reference"
    VERBATIM
)

add_custom_target(w01d01_runtime_error_check
    COMMAND bash -c
            "if '$<TARGET_FILE:w01d01_runtime_error>'; then echo 'expected runtime failure, but program exited successfully'; exit 1; else echo 'observed expected runtime failure'; fi"
    DEPENDS w01d01_runtime_error
    COMMENT "Run Day1 runtime_error.cpp and confirm the expected runtime failure"
    VERBATIM
)

add_custom_target(w01d01_all
    DEPENDS
        w01d01_warning_fixed
        w01d01_runtime_error
)
