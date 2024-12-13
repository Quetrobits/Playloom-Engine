#include <iostream>
#include <cassert>

// Example function to be tested
int add(int a, int b) {
    return a + b;
}

int main() {
    // Unit test for add function
    assert(add(2, 3) == 5);
    assert(add(-1, 1) == 0);
    std::cout << "All tests passed!" << std::endl;

    return 0;
}