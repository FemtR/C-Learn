#include <iostream>
#include <vector>

int Add(int a, int b) {
    return a + b;
}

int main() {
    int x = 3;
    std::vector<int> values = {1, 2, 3};
    std::size_t index = 1;

    if (x == 3) {
        std::cout << Add(x, 2) << '\n';
    }

    if (index < values.size()) {
        std::cout << values[index] << '\n';
    }

    return 0;
}
