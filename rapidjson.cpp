#include "rapidjson.h"

Rapidjson::Rapidjson() {}

WeatherData Rapidjson::parseCurrentWeather(const std::string &jsonString) {
    WeatherData data;
    rapidjson::Document doc;

    if (doc.Parse(jsonString.c_str()).HasParseError()) return data;

    // Parse current weather...
    if (doc.HasMember("current_weather") && doc["current_weather"].IsObject()) {
        const auto &cw = doc["current_weather"];
        if (cw.HasMember("temperature")) data.temperature = cw["temperature"].GetDouble();
        if (cw.HasMember("windspeed")) data.windSpeed = cw["windspeed"].GetDouble();
    }

    // Parse 7-day daily forecast
    if (doc.HasMember("daily") && doc["daily"].IsObject()) {
        const auto &daily = doc["daily"];
        if (daily.HasMember("temperature_2m_max") && daily["temperature_2m_max"].IsArray()) {
            for (const auto &val : daily["temperature_2m_max"].GetArray()) {
                if (val.IsNumber()) data.dailyMaxTemp.push_back(val.GetDouble());
            }
        }
    }

    return data;
}