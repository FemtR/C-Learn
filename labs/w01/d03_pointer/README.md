# Day3：指针、引用与悬空对象

## 今日目标

理解指针、引用、`nullptr` 和对象生命周期之间的关系。

今天重点不是背语法，而是判断：

```text
1. 指针是否可能为空？
2. 指针或引用指向的对象是否还活着？
3. 返回值应该让调用者拥有，还是只观察已有对象？
```

## 运行命令

```bash
cmake -S . -B build
cmake --build build --target w01d03_pointer
./build/w01d03_pointer
ctest --test-dir build --output-on-failure
```

## 跟写顺序

### 1. 先写安全的按值返回

```cpp
int ReturnLocalValue() {
    int value = 42;
    return value;
}
```

局部变量 `value` 会在函数结束时销毁，但返回的是一个 `int` 值，调用者拿到的是自己的结果。

### 2. 修复返回局部引用

坏写法：

```cpp
int& BadLocalReference() {
    int value = 42;
    return value;
}
```

最小修复：

```cpp
int FixLocalReference() {
    int value = 42;
    return value;
}
```

判断：返回局部引用不安全，因为函数结束后局部对象已销毁。

### 3. 修复返回局部指针

坏写法：

```cpp
int* BadLocalPointer() {
    int value = 42;
    return &value;
}
```

最小修复：

```cpp
int FixLocalPointer() {
    int value = 42;
    return value;
}
```

判断：返回局部变量地址不安全，因为地址指向的对象已经不存在。

### 4. 修复 delete 后继续使用

坏写法：

```cpp
std::string* name = new std::string("laser");
delete name;
std::cout << *name;
```

最小修复：不要手写 `new/delete`，能用局部对象和值返回就先用它。

```cpp
std::string FixUseAfterDelete() {
    std::string name = "laser";
    return name;
}
```

### 5. 修复空指针解引用

坏写法：

```cpp
int BadNullDereference(const int* value) {
    return *value;
}
```

最小修复：使用前检查 `nullptr`。

```cpp
std::optional<int> FixNullDereference(const int* value) {
    if (value == nullptr) {
        return std::nullopt;
    }
    return *value;
}
```

### 6. 修复 `GetName`

坏写法：

```cpp
const char* BadCString() {
    std::string name = "robot";
    return name.c_str();
}
```

最小修复：

```cpp
std::string GetName() {
    std::string name = "robot";
    return name;
}
```

`std::string` 拥有字符缓冲区。局部 `name` 销毁后，`name.c_str()` 返回过的指针也失效。

## 今日验收问题

1. 为什么返回局部变量的引用不安全？
2. 为什么返回局部变量的地址不安全？
3. `delete p` 之后，`p` 变量本身和它指向的对象分别是什么状态？
4. 指针和引用谁可以为空？
5. 为什么 `GetName()` 应该返回 `std::string`，而不是 `const char*`？

## 今日总结

```text
引用必须绑定对象，但不保证对象永远活着。
指针可以为空，所以解引用前要确认。
函数内部创建的新结果，优先按值返回。
```
