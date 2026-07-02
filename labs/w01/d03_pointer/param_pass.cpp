#include <iostream>
#include <string>

// 1. 按值传递 (Pass by Value)
// 会创建副本，函数内部的修改不影响外部变量
void IncrementByValue(int x) {
    x += 1;
    std::cout << "  Inside IncrementByValue: x = " << x << " (address: " << &x << ")\n";
}

// 2. 指针传递 (Pass by Pointer)
// 传递的是变量的地址。可以通过指针修改外部变量。
// 注意：指针可能为 nullptr，所以必须进行空指针检查！
void IncrementByPointer(int* p) {
    if (p == nullptr) {
        std::cout << "  Inside IncrementByPointer: pointer is nullptr!\n";
        return;
    }
    *p += 1;
    std::cout << "  Inside IncrementByPointer: *p = " << *p << " (address: " << p << ")\n";
}

// 3. 引用传递 (Pass by Reference)
// 传递的是变量的别名（即同一个变量本身）。可以直接修改外部变量。
// 安全性高：引用不需要且不能进行 nullptr 检查，它必定指向一个有效对象。
void IncrementByReference(int& r) {
    r += 1;
    std::cout << "  Inside IncrementByReference: r = " << r << " (address: " << &r << ")\n";
}

// 4. 常量引用传递 (Pass by Const Reference)
// 避免了大对象的复制开销，同时保证函数内部无法修改该对象（只读）。
void PrintStringByConstReference(const std::string& s) {
    // s += " modified"; // 如果取消注释这行，会导致编译错误，因为有 const 修饰，无法修改
    std::cout << "  Inside PrintStringByConstReference: \"" << s << "\" (address: " << &s << ")\n";
}

int main() {
    int val = 10;
    std::cout << "Original val = " << val << " (address: " << &val << ")\n\n";

    // 测试 1：值传递
    std::cout << "--- Testing Pass by Value ---\n";
    IncrementByValue(val);
    std::cout << "After IncrementByValue, val = " << val << "\n\n";

    // 测试 2：指针传递
    std::cout << "--- Testing Pass by Pointer ---\n";
    IncrementByPointer(&val);
    std::cout << "After IncrementByPointer, val = " << val << "\n\n";

    // 测试 2b：传递 nullptr 到指针参数
    std::cout << "--- Testing Pass by Pointer with nullptr ---\n";
    IncrementByPointer(nullptr);
    std::cout << "\n";

    // 测试 3：引用传递
    std::cout << "--- Testing Pass by Reference ---\n";
    IncrementByReference(val);
    std::cout << "After IncrementByReference, val = " << val << "\n\n";

    // 测试 4：常量引用传递
    std::cout << "--- Testing Pass by Const Reference ---\n";
    std::string text = "Hello C++";
    std::cout << "Original text = \"" << text << "\" (address: " << &text << ")\n";
    PrintStringByConstReference(text);
    std::cout << "\n";

    return 0;
}
