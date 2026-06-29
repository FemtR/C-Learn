# Day2：对象生命周期

## 今日目标

理解 C++ 对象什么时候构造、什么时候析构，并能根据代码预测输出顺序。

今天重点观察 4 类对象：

- 普通局部对象
- 内部作用域对象
- `new/delete` 管理的动态对象
- `static` 局部对象

## 运行命令

```bash
cmake -S . -B build
cmake --build build --target w01d02_lifetime
./build/w01d02_lifetime
ctest --test-dir build --output-on-failure
```

## 输出记录

```text
construct: local_a
construct: local_b
destruct: local_b
destruct: local_a
construct: nested_scope_a
construct: nested_scope_b
construct: nested_scope_c
destruct: nested_scope_c
destruct: nested_scope_b
construct: nested_scope_d
destruct: nested_scope_d
destruct: nested_scope_a
construct: heap object
destruct: heap object
construct: static object
destruct: static object
```

## 输出解读

### 1. 普通局部对象

```text
construct: local_a
construct: local_b
destruct: local_b
destruct: local_a
```

结论：

```text
同一作用域内，局部对象按定义顺序构造，按相反顺序析构。
```

### 2. 内部作用域对象

```text
construct: nested_scope_a
construct: nested_scope_b
construct: nested_scope_c
destruct: nested_scope_c
destruct: nested_scope_b
construct: nested_scope_d
destruct: nested_scope_d
destruct: nested_scope_a
```

结论：

```text
对象离开自己所属的作用域时析构，不一定等到整个函数结束。
```

内部 `{}` 中的 `b` 和 `c` 会先析构，然后外层代码才继续构造 `d`。

### 3. 动态对象

```text
construct: heap object
destruct: heap object
```

结论：

```text
new 创建的对象不会因为函数结束自动析构，必须 delete 才会析构。
```

如果只有 `new` 没有 `delete`，对象析构函数不会执行，会造成资源泄漏。

### 4. static 局部对象

```text
construct: static object
destruct: static object
```

结论：

```text
static 局部对象第一次执行到定义处时构造，只构造一次，程序结束时析构。
```

虽然代码里调用了两次 `StaticObject()`，但 `static object` 只构造了一次。

## 今日验收答案

### 1. 同一作用域内，多个局部对象的析构顺序是什么？

构造顺序和定义顺序一致，析构顺序和构造顺序相反。

### 2. 内部 `{}` 作用域里的对象什么时候析构？

离开内部 `{}` 作用域时立即析构，不会等到外层函数结束。

### 3. `new Tracer(...)` 创建的对象什么时候析构？

执行 `delete` 时析构。如果没有 `delete`，对象不会自动析构。

### 4. `static` 局部对象会构造几次？什么时候析构？

只构造一次，第一次执行到定义语句时构造；程序结束时析构。

### 5. 为什么对象生命周期是 RAII 和智能指针的基础？

因为 C++ 可以利用对象析构函数自动释放资源。局部对象离开作用域会自动析构，所以可以把内存、锁、文件、线程等资源绑定到对象生命周期上。

## 今日总结

判断一个对象生命周期时，先问：

```text
1. 它在哪里定义？
2. 它属于哪个作用域？
3. 它是普通局部对象、动态对象，还是 static 对象？
4. 谁负责触发它的析构？
```

Day2 的核心结论：

```text
C++ 用对象生命周期管理资源。
```
