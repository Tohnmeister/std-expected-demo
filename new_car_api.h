#pragma once

#include <expected>
#include <string>

enum class CarApiError {
    NO_CONNECTION,
    CACHE_CORRUPT,
    DATA_NOT_AVAILABLE,
};

struct DiagnosticData {
    int error_code;
};

class CarStatus {
public:
    std::expected<DiagnosticData, CarApiError> get_diagnostic_data() const {
        const bool success = rand() % 2;
        if (!success)
            return std::unexpected{CarApiError::DATA_NOT_AVAILABLE};

        return DiagnosticData{42};
    }

};

std::expected<CarStatus, CarApiError> fetch_car_status_through_http() {
    const bool success = rand() % 2;

    if (!success)
        return std::unexpected{CarApiError::NO_CONNECTION};

    return CarStatus{};
}

std::expected<CarStatus, CarApiError> fetch_car_status_through_cache() {
    const bool success = rand() % 2;

    if (!success)
        return std::unexpected{CarApiError::CACHE_CORRUPT};

    return CarStatus{};
}