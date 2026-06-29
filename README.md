# C-Learn

8 周 C++17 工程能力学习仓库，面向 SLAM 工程实践。

## 常用命令

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure
```

## Day1 示例目标

```bash
cmake --build build --target w01d01_all
cmake --build build --target w01d01_preprocess
cmake --build build --target w01d01_warning_bad_check
cmake --build build --target w01d01_link_error_check
cmake --build build --target w01d01_runtime_error_check
```
