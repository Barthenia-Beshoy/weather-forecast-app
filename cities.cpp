#include "cities.h"

Cities::Cities() {
    // Populate predefined cities (Latitude, Longitude)
    cityMap["Cairo"] = {30.0444, 31.2357};
    cityMap["London"] = {51.5074, -0.1278};
    cityMap["New York"] = {40.7128, -74.0060};
    cityMap["Tokyo"] = {35.6762, 139.6503};
}

Location Cities::getLocation(const std::string &cityName) const {
    auto it = cityMap.find(cityName);
    if (it != cityMap.end()) {
        return it->second;
    }
    return {0.0, 0.0};
}

std::string Cities::getApiUrl(const std::string &cityName) const {
    Location loc = getLocation(cityName);
    return "https://api.open-meteo.com/v1/forecast?latitude=" +
            std::to_string(loc.latitude) +
            "&longitude=" + std::to_string(loc.longitude) +
            "&current_weather=true&daily=temperature_2m_max&timezone=auto";

}