#include <iostream>

// Imagine having a function that


int divide(int numerator, int denominator) {
    return numerator / denominator;
}


int main() {
    std::cout << divide(3, 0) << '\n';
    return 0;
}