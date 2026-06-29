# Day1：编译、链接、运行与警告意识

## 今日目标

理解一份 C++ 源文件如何经历：

```text
预处理 -> 编译 -> 汇编 -> 链接 -> 运行
```

今天必须能区分：

- 编译错误：语法、类型、声明等问题，导致 `.o` 不能生成。
- 链接错误：目标文件能生成，但最终可执行文件无法生成。
- 运行时错误：程序能生成，但运行时崩溃或行为错误。

## 文件说明

```text
warning_bad.cpp
warning_fixed.cpp
link_error.cpp
runtime_error.cpp
```

- `warning_bad.cpp`：故意制造警告。
- `warning_fixed.cpp`：修复警告后的版本。
- `link_error.cpp`：制造 `undefined reference` 链接错误。
- `runtime_error.cpp`：制造运行时错误。

## 必跑命令

所有命令都从仓库根目录执行。

### 0. 配置构建目录

```bash
cmake -S . -B build
```

验收点：CMake 能识别 C++17 项目，并生成构建文件。

### 1. 正常构建 Day1 可编译目标

```bash
cmake --build build --target w01d01_all
```

验收点：`warning_fixed.cpp` 和 `runtime_error.cpp` 都能通过严格警告选项编译。

### 2. 运行修复后的警告示例

```bash
./build/w01d01_warning_fixed
```

验收点：程序输出两行：

```text
5
2
```

### 3. 观察预处理结果

```bash
cmake --build build --target w01d01_preprocess
```

验收点：能在输出中看到预处理后文件的行数，并解释为什么包含 `<iostream>` 后结果会变得很大。

### 4. 观察警告

```bash
cmake --build build --target w01d01_warning_bad_check
```

验收点：能指出每个警告对应的代码位置和潜在风险。

需要观察到的 3 类警告：

- 未使用变量。
- `if` 条件中误写赋值。
- 有符号整数与无符号整数比较。

### 5. 观察链接错误

```bash
cmake --build build --target w01d01_link_error_check
```

验收点：能解释 `undefined reference` 的原因：函数只有声明，没有定义。

### 6. 观察运行时错误

```bash
cmake --build build --target w01d01_runtime_error_check
```

验收点：能解释为什么程序能编译链接，但运行时会崩溃或异常退出。

### 7. 运行测试

```bash
ctest --test-dir build --output-on-failure
```

验收点：`w01d01_warning_fixed_runs` 通过。

## 额外理解：`.o` 文件

正常学习流程使用 CMake；如果要单独观察“只编译不链接”的产物，可以在根目录执行：

```bash
g++ -std=c++17 -Wall -Wextra -Wpedantic -c labs/w01/d01_compile_flow/warning_fixed.cpp -o /tmp/day01_main.o
```

验收点：能解释 `.o` 不是最终程序，它还需要链接。

## 今日验收问题

1. `g++ -c main.cpp -o main.o` 生成的是什么？它能直接运行吗？
2. `undefined reference` 属于编译错误、链接错误还是运行时错误？
3. `-Wall -Wextra -Wpedantic` 分别用来做什么？
4. 为什么警告不能随便忽略？
5. 编译错误、链接错误、运行时错误的边界分别是什么？

## 今日笔记

实际执行过的命令：

```bash

```

观察到的警告/错误：

```text

```

我的回答：

1. 
2. 
3. 
4. 
5. 

## 今日提交

完成后提交：

```bash
git add docs/learning_log.md labs/w01/d01_compile_flow
git commit -m "w1d1: practice compile link runtime errors"
```
