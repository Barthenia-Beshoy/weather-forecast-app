#include "curl.h"
#include <curl/curl.h>

static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp) {
    size_t totalSize = size * nmemb;
    std::string *str = static_cast<std::string*>(userp);
    str->append(static_cast<char*>(contents), totalSize);
    return totalSize;
}

Curl::Curl() { // Capital 'C'
    curl_global_init(CURL_GLOBAL_DEFAULT);
}

Curl::~Curl() { // Capital 'C'
    curl_global_cleanup();
}

std::string Curl::fetchData(const std::string &url) { // Capital 'C'
    CURL *curl_handle = curl_easy_init();
    std::string readBuffer;

    if (curl_handle) {
        curl_easy_setopt(curl_handle, CURLOPT_URL, url.c_str());
        curl_easy_setopt(curl_handle, CURLOPT_WRITEFUNCTION, WriteCallback);
        curl_easy_setopt(curl_handle, CURLOPT_WRITEDATA, &readBuffer);
        curl_easy_setopt(curl_handle, CURLOPT_CONNECTTIMEOUT, 5L); // 5 sec max to connect
        curl_easy_setopt(curl_handle, CURLOPT_TIMEOUT, 10L);

        CURLcode res = curl_easy_perform(curl_handle);
        if (res != CURLE_OK) {
            // Request failed, handle or log error if needed
        }
        curl_easy_cleanup(curl_handle);
    }
    return readBuffer;
}