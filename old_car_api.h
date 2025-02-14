#pragma once

#include <memory>
#include <string>
#include <variant>

enum class CarApiResult {
    SUCCESS,
    NO_CONNECTION,
    CACHE_CORRUPT,
    DATA_NOT_AVAILABLE,
};

struct DiagnosticData {
    int error_code;
};

class CarStatus {
public:
    CarApiResult get_diagnostic_data(std::unique_ptr<DiagnosticData>& diagnostic_data) const {
        const bool success = rand() % 2;
        if (!success) {
            return CarApiResult::DATA_NOT_AVAILABLE;
        }

        diagnostic_data = std::make_unique<DiagnosticData>(42);
        return CarApiResult::SUCCESS;
    }

};

CarApiResult fetch_car_status_through_http(std::unique_ptr<CarStatus>& car_status) {
    const bool success = rand() % 2;

    if (!success)
        return CarApiResult::NO_CONNECTION;

    car_status = std::make_unique<CarStatus>();
    return CarApiResult::SUCCESS;
}

CarApiResult fetch_car_status_through_cache(std::unique_ptr<CarStatus>& car_status) {
    const bool success = rand() % 2;

    if (!success)
        return CarApiResult::CACHE_CORRUPT;

    return CarApiResult::SUCCESS;
}