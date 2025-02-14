#include <iostream>
#include <format>

/**
 * Simple function that divides two integers. Its return value is not the division result, but rather an status code.
 * @param numerator Numerator
 * @param denominator Denominator. Must not be 0.
 * @param result The result of the division, or unchanged if an error occurred.
 * @return 0 if success, -1 otherwise
 */
int divide1(int numerator, int denominator, int& result) {
    if (denominator == 0) return -1; // Error code
    result = numerator / denominator;
    return 0; // Success
}

/**
 * Alternative function that divides two integers. Now using exceptions. So the return value is the result of the
 * division.
 * @param numerator Numerator
 * @param denominator Denominator. Must not be 0.
 * @return The result of the division.
 * @throws std::invalid_argument in case the denominator is 0.
 */
int divide2(int numerator, int denominator) {
    if (denominator == 0) throw std::invalid_argument("Denominator cannot be zero");
    return numerator / denominator;
}

int main() {
    // Using return codes
    int result;
    if (divide1(10, 0, result) != 0) {
        std::cout << "Error: Division by zero!\n";
    } else {
        std::cout << "Result: " << result << '\n';
    }

    // Using exceptions
    try {
        result = divide2(10, 0);
        std::cout << "Result: " << result << '\n';
    } catch (const std::invalid_argument& e) {
        std::cout << std::format("Error: {}\n", e.what());
    }
    return 0;
}