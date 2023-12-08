#ifndef HTTPCLIENT_H
#define HTTPCLIENT_H

#include <string>

#include "AxisImg.h"

class HttpClient
{
public:
    struct GetRequest
    {
        std::string url;
        std::string fileName;
        std::string userName;
        std::string password;
    };

    struct PostRequest
    {
        std::string url;
        AxisImg img;
    };

public:
    HttpClient() = default;
    int httpGetRequest(const GetRequest& request);
    int httpPostRequest(const PostRequest& request);
};

#endif // HTTPCLIENT_H
