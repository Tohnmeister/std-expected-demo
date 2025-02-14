#pragma once

#include <expected>
#include <string>

enum class car_api_error {
    no_connection,
    data_not_available
};

struct diagnostic_data {
    int error_code;
};

class car_status {
public:
    std::expected<diagnostic_data, car_api_error> get_diagnostic_data() {
        const bool success = rand() % 2;
        if (!success)
            return std::unexpected{car_api_error::data_not_available};

        return diagnostic_data{42};
    }

};

std::expected<car_status, car_api_error> fetch_car_status_through_http() {
    const bool success = rand() % 2;

    if (!success)
        return std::unexpected{car_api_error::no_connection};

    return car_status{};
}
