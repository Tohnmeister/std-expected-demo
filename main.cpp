#include <iostream>
#include <format>
#include <expected>
#include <complex>
#include "old_car_api.h"

/**
 * Simple function that divides two integers. Its return value is not the division result, but rather an status code.
 * @param numerator Numerator
 * @param denominator Denominator. Must not be 0.
 * @param result The result of the division, or unchanged if an error occurred.
 * @return 0 if SUCCESS, -1 otherwise
 */
int divide1(int numerator, int denominator, int& result) {
    if (denominator == 0) return -1; // Error code
    result = numerator / denominator;
    return 0; // SUCCESS
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
    if (denominator == 0) throw std::invalid_argument("Denominator is zero");
    return numerator / denominator;
}

// A few problems with both approaches:
// - Unclear/weird signature
// - Exceptions must be documented and handled well, otherwise you'll end up with uncaught exceptions, possibly
//   terminating the program.


// Now define the function
std::expected<int, std::string> divide3(int numerator, int denominator) {
    if (denominator == 0) return std::unexpected{"Denominator is zero"};
    return numerator / denominator;
}

std::expected<int, std::string> square_root(int n) {
    if (n < 0) return std::unexpected{"Negative number"};
    return std::sqrt(n);
}

// Pitfalls
// - failure to check has_value()

// Limitations
// - Default constructible

// Special cases
// - or_else
// - and_then
// - transform
// - value_or
// - value() on an rvalue std::expected

int main() {
    srand(time(nullptr));

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
        std::cout << std::format("Result: {}\n", result);
    } catch (const std::invalid_argument& e) {
        std::cout << std::format("Error: {}\n", e.what());
    }

    // Using std::exception
    auto result3 = divide3(10, 0);
    if (result3.has_value()) {
        std::cout << std::format("Result: {}\n", result3.value());
    } else {
        std::cout << std::format("Error: {}\n", result3.error());
    }

    // Now let's say, I'd like to have a fallback value, in case something goes wrong.
    int result4 = divide3(10, 0).value_or(42);
    std::cout << std::format("Result: {}\n", result4);

    // and_then
    // Now let's say, I'd like to continue with the value, putting it into another function that might fail.
    auto result5 = divide3(10, -1).and_then(square_root);

    std::cout << std::format("Result: {}\n", result5.error());

    std::cout << std::sqrt(-1) << '\n';

    // transform
    // Multiply by PI
    auto result6 = divide3(10, 1).and_then(square_root).transform([](int n) { return n * 42; });

    // value_or
    auto result7 = divide3(10, -2)
            .and_then(square_root)
            .transform([](int n) { return std::format("Result: {}", n); })
            .transform_error([](const std::string& err) { return std::format("Error: {}", err); });

    if (result7.has_value()) {
        std::cout << result7.value() << '\n';
    } else {
        std::cout << result7.error() << '\n';
    }

    // Now the entire example but then with CarStatus and DiagnosticData.
    std::unique_ptr<CarStatus> car_status;
    if (fetch_car_status_through_http(car_status) == CarApiResult::SUCCESS || fetch_car_status_through_cache(car_status) == CarApiResult::SUCCESS) {
        std::unique_ptr<DiagnosticData> diagnostic_data;
        if (car_status->get_diagnostic_data(diagnostic_data) == CarApiResult::SUCCESS) {
            std::cout << std::format("Car Diagnostics Error Code: {}\n", diagnostic_data->error_code);
        } else {
            std::cout << "Error occurred fetching diagnostic data\n";
        }
    } else {
        std::cout << "Error occurred fetching car status\n";
    }

    return 0;
}