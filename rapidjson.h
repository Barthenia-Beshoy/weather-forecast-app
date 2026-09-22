#ifndef RAPIDJSON_H
#define RAPIDJSON_H

#include <string>
#include "rapidjson/document.h"

#include <vector>

struct WeatherData {
    double temperature = 0.0;
    double windSpeed = 0.0;
    int weatherCode = 0;
    std::vector<double> dailyMaxTemp; // 7-day max temperatures
    std::vector<std::string> dailyDates; // Dates/Days
};

class Rapidjson {
public:
    Rapidjson();
    WeatherData parseCurrentWeather(const std::string &jsonString);
};

#endif // RAPIDJSON_H