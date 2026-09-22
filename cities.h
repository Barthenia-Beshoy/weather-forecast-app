#ifndef CITIES_H
#define CITIES_H

#include <string>
#include <map>

struct Location {
    double latitude;
    double longitude;
};

class Cities {
private:
    std::map<std::string, Location> cityMap;

public:
    Cities();
    Location getLocation(const std::string &cityName) const;
    std::string getApiUrl(const std::string &cityName) const;
};

#endif // CITIES_H