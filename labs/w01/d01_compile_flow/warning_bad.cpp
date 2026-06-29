#include <iostream>
#include <vector>

int Add(int a, int b) {
    return a + b;
}

int main() {
    int unused = 42;

    int x = 10;
    std::vector<int> values = {1, 2, 3};
    int index = -1;

    if (x = 3) {
        std::cout << Add(x, 2) << '\n';
    }
    //index是-1,是有符号整数，values.size()是无符号整数，比较的时候 -1可能被转换为一个很大的无符号数。
    if (index < values.size()) {
        std::cout << values[index] << '\n';
    }

    return 0;
}
