#ifndef CURL_H
#define CURL_H

#include <string>

class Curl {
public:
    Curl();
    ~Curl();
    std::string fetchData(const std::string &url);
};

#endif // CURL_H