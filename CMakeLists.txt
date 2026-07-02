# CMakeLists.txt 是这个学习仓库的构建入口。
#
# 读这个文件时先记住三步：
# 1. 配置：`cmake -S . -B build`
#    CMake 读取本文件，并在 build/ 目录下生成 Makefile 或 Ninja 文件。
# 2. 构建：`cmake --build build`
#    生成出来的构建系统会调用真正的 C++ 编译器。
# 3. 测试：`ctest --test-dir build --output-on-failure`
#    CTest 会运行下面用 add_test() 注册的测试。

# 要求 CMake 版本至少为 3.16。版本太低时直接停止配置。
cmake_minimum_required(VERSION 3.16)

# 定义项目名称，并说明这个项目只启用 C++ 语言。
project(CLearn LANGUAGES CXX)

# 仓库里的所有 target 默认使用 C++17。
set(CMAKE_CXX_STANDARD 17)

# 如果编译器不支持 C++17，就让 CMake 配置失败。
# 这样可以避免悄悄降级到旧标准。
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 关闭编译器扩展，例如 GNU++17。
# 这样代码更接近标准 C++17，移植性更好。
set(CMAKE_CXX_EXTENSIONS OFF)

# 启用 CTest。启用后才能使用 add_test() 注册测试。
include(CTest)

# 给某个 target 添加统一的警告选项。
#
# target_compile_options(... PRIVATE ...)
# 表示这些编译选项只作用于这个 target 自己。
function(apply_common_warnings target)
    target_compile_options(${target} PRIVATE
        -Wall
        -Wextra
        -Wpedantic
    )
endfunction()

# 每日练习程序的辅助函数。
#
# 如果不用这个函数，正常 CMake 写法是：
#   add_executable(name file.cpp)
#   target_compile_options(name PRIVATE -Wall -Wextra -Wpedantic)
#
# 这里把两行封装成一个函数，保证每个练习程序默认都有同样的警告选项。
function(add_lab_executable target source)
    add_executable(${target} ${source})
    apply_common_warnings(${target})
endfunction()

# ---------------------------------------------------------------------------
# 第 1 周 / 第 1 天：编译、链接、运行与警告意识。
# ---------------------------------------------------------------------------

# 把 Day1 源码目录保存到变量里，后面写 target 时更清楚。
# CMAKE_CURRENT_SOURCE_DIR 表示当前 CMakeLists.txt 所在目录，也就是仓库根目录。
set(W01D01_DIR ${CMAKE_CURRENT_SOURCE_DIR}/labs/w01/d01_compile_flow)

# Day1 的临时生成文件放到 build/labs/...，不要污染源码目录。
# CMAKE_CURRENT_BINARY_DIR 表示当前构建目录，通常就是 ./build。
set(W01D01_BUILD_DIR ${CMAKE_CURRENT_BINARY_DIR}/labs/w01/d01_compile_flow)

# 一个正常的可执行程序 target。
#
# 构建：
#   cmake --build build --target w01d01_warning_fixed
#
# 运行：
#   ./build/w01d01_warning_fixed
add_lab_executable(w01d01_warning_fixed
    ${W01D01_DIR}/warning_fixed.cpp
)

# 这个程序会在运行时故意崩溃。
# 它仍然可以作为构建目标，因为它用来说明：
# “能编译、能链接”不等于“运行时一定正确”。
add_lab_executable(w01d01_runtime_error
    ${W01D01_DIR}/runtime_error.cpp
)

# 你的 Day1 自测程序。
add_lab_executable(w01d01_check_task
    ${W01D01_DIR}/check_task.cpp
)

# 把可执行程序注册成测试。
#
# NAME 是 CTest 里的测试名。
# COMMAND 是要运行的可执行程序 target。
#
# 运行全部测试：
#   ctest --test-dir build --output-on-failure
add_test(NAME w01d01_check_task_runs COMMAND w01d01_check_task)
add_test(NAME w01d01_warning_fixed_runs COMMAND w01d01_warning_fixed)

# 自定义 target：只执行预处理阶段。
#
# ${CMAKE_CXX_COMPILER} 是 CMake 选中的真实 C++ 编译器，
# 例如 /usr/bin/c++。
#
# -E 表示“只预处理”。它会展开 #include 和宏，
# 然后把结果写入 warning_fixed.i。
add_custom_target(w01d01_preprocess
    COMMAND ${CMAKE_COMMAND} -E make_directory ${W01D01_BUILD_DIR}
    COMMAND ${CMAKE_CXX_COMPILER}
            -std=c++17
            -E
            ${W01D01_DIR}/warning_fixed.cpp
            -o ${W01D01_BUILD_DIR}/warning_fixed.i
    COMMAND wc -l ${W01D01_BUILD_DIR}/warning_fixed.i
    COMMENT "预处理 Day1 的 warning_fixed.cpp，并统计展开后的行数"
    VERBATIM
)

# 自定义 target：编译一个故意带 warning 的文件。
#
# 它不放进默认构建，因为它本来就是用来观察 warning 的。
# 手动执行：
#   cmake --build build --target w01d01_warning_bad_check
add_custom_target(w01d01_warning_bad_check
    COMMAND ${CMAKE_CXX_COMPILER}
            -std=c++17
            -Wall
            -Wextra
            -Wpedantic
            ${W01D01_DIR}/warning_bad.cpp
            -o ${W01D01_BUILD_DIR}/warning_bad
    COMMENT "编译 Day1 的 warning_bad.cpp，用来观察编译器 warning"
    VERBATIM
)

# 自定义 target：确认链接错误。
#
# link_error.cpp 声明了 Add()，也调用了 Add()，但没有定义 Add()。
# 编译器只需要看到声明，所以能通过编译；
# 链接器需要找到函数体，所以会报 undefined reference。
#
# 下面的 shell 判断把结果反过来：
# - 如果编译/链接居然成功了，说明不符合预期，让 target 失败；
# - 如果出现预期中的链接错误，说明实验成功，让 target 通过。
add_custom_target(w01d01_link_error_check
    COMMAND ${CMAKE_COMMAND} -E make_directory ${W01D01_BUILD_DIR}
    COMMAND bash -c
            "if '${CMAKE_CXX_COMPILER}' -std=c++17 -Wall -Wextra -Wpedantic '${W01D01_DIR}/link_error.cpp' -o '${W01D01_BUILD_DIR}/link_error'; then echo 'expected link failure, but build succeeded'; exit 1; else echo 'observed expected link failure'; fi"
    COMMENT "构建 Day1 的 link_error.cpp，并确认出现预期的 undefined reference"
    VERBATIM
)

# 自定义 target：确认运行时错误。
#
# DEPENDS 表示先构建 w01d01_runtime_error，再运行这个检查 target。
# 这个程序会解引用 nullptr，所以应该在运行时失败。
add_custom_target(w01d01_runtime_error_check
    COMMAND bash -c
            "if '$<TARGET_FILE:w01d01_runtime_error>'; then echo 'expected runtime failure, but program exited successfully'; exit 1; else echo 'observed expected runtime failure'; fi"
    DEPENDS w01d01_runtime_error
    COMMENT "运行 Day1 的 runtime_error.cpp，并确认出现预期的运行时错误"
    VERBATIM
)

# Day1 正常可构建程序的集合 target。
#
# 这个 target 只依赖“应该能干净编译和链接”的程序。
# 故意产生 warning、链接错误、运行时错误的例子放在上面的独立 target 里。
add_custom_target(w01d01_all
    DEPENDS
        w01d01_warning_fixed
        w01d01_runtime_error
        w01d01_check_task
)

# ---------------------------------------------------------------------------
# 第 1 周 / 第 3 天：指针、引用、nullptr 与悬空对象。
# ---------------------------------------------------------------------------

set(W01D03_DIR ${CMAKE_CURRENT_SOURCE_DIR}/labs/w01/d03_pointer)

add_lab_executable(w01d03_pointer
    ${W01D03_DIR}/pointer.cpp
)

add_lab_executable(w01d03_param_pass
    ${W01D03_DIR}/param_pass.cpp
)

add_test(NAME w01d03_pointer_runs COMMAND w01d03_pointer)
add_test(NAME w01d03_param_pass_runs COMMAND w01d03_param_pass)
