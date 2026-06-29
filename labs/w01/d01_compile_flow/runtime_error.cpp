#include <iostream>

int main() {
    int* value = nullptr;
    std::cout << "About to dereference a null pointer\n";
    std::cout << *value << '\n';
    return 0;
}
