#include <iostream>

#include "AxisImg.h"
#include "HttpClient.h"
#include "Utils.h"

using namespace std;

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        cout << "Missed argument for config file" << endl;
        return 0;
    }

    utils::Configs config;
    const char* filename = argv[1];
    if (!utils::loadConfigs(filename, config))
    {
        cout << "Cannot load config file " << filename << endl;
        return 0;
    }

    HttpClient httpClient;
    HttpClient::GetRequest getRequest =
    {
        .url = config.axisCgiUrl,
        .fileName = config.outBinFile,
        .userName = config.userName,
        .password = config.password
    };

    cout << "Retrieve data from the cammera (GET request): " << endl;
    httpClient.httpGetRequest(getRequest);

    AxisImg img(config.outBinFile);
    cout << "Received file " << config.outBinFile << " (" << img.data().size() << " Bytes)"<< endl;

    cout << "Pack image into xml file" << endl;
    if (img.saveAsXml(config.outXmlFile) < 0)
    {
        cout << "Failed to save xml file: " << config.outXmlFile << endl;
    }
    else
    {
        cout << "Created XML file: " << config.outXmlFile << endl;
    }

    cout << "Upload xml file to http server (POST request): " << endl;
    const HttpClient::PostRequest postRequest =
    {
        .url = config.httpServerUrl,
        .img = AxisImg(config.outXmlFile)
    };

    httpClient.httpPostRequest(postRequest);

    return 0;
}
