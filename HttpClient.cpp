#include "HttpClient.h"

#include <curl/curl.h>
#include <iostream>
#include <stdio.h>

static size_t write_data(void *ptr, size_t size, size_t nmemb, FILE *stream) {
    size_t written = fwrite(ptr, size, nmemb, stream);
    return written;
}

int HttpClient::httpGetRequest(const GetRequest &request)
{
    int httpResutlCode = -1;
    CURL *curl = curl_easy_init();
    if (curl)
    {
        FILE *saveFile;
        saveFile = fopen(request.fileName.c_str(), "wb");
        if (saveFile)
        {
            curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_data);
            curl_easy_setopt(curl, CURLOPT_WRITEDATA, saveFile);
        }
        else
        {
            std::cout << "Failed to open file " << request.fileName << std::endl;
        }

        curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());
        curl_easy_setopt(curl, CURLOPT_HTTPAUTH, (long)CURLAUTH_ANY);
        curl_easy_setopt(curl, CURLOPT_USERPWD, (request.userName + ":" + request.password).c_str());

        const CURLcode res = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpResutlCode);
        if (res != CURLE_ABORTED_BY_CALLBACK)
        {
            std::cout << "HTTP GET response " << httpResutlCode << std::endl;
        }
        else
        {
            httpResutlCode = -1;
            std::cout << "HTTP GET aborted by callback" << std::endl;
        }
        curl_easy_cleanup(curl);
        fclose(saveFile);

    }
    else
    {
        std::cout << "Failed to initialize curl" << std::endl;
    }

    return httpResutlCode;

}

int HttpClient::httpPostRequest(const PostRequest &request)
{
    int httpResutlCode = -1;
    CURL *curl = curl_easy_init();
    if (curl)
    {
        curl_easy_setopt(curl, CURLOPT_URL, request.url.c_str());
        curl_easy_setopt(curl, CURLOPT_CUSTOMREQUEST, "POST");
        const std::string PostData = request.img.data();
        curl_easy_setopt(curl, CURLOPT_POSTFIELDS, PostData.c_str());

        const auto res = curl_easy_perform(curl);

        curl_easy_getinfo(curl, CURLINFO_RESPONSE_CODE, &httpResutlCode);
        if (res != CURLE_ABORTED_BY_CALLBACK)
        {
            std::cout << "HTTP POST response " << httpResutlCode << std::endl;
        }
        else
        {
            httpResutlCode = -1;
            std::cout << "HTTP POST aborted by callback" << std::endl;
        }
    }
    else
    {
        std::cout << "Failed to initialize curl" << std::endl;
    }

    return httpResutlCode;
}
