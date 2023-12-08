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
//    const char* filename = "/home/marta/dev/cammera_acap/configs.xml";
    const char* filename = argv[1];
    if (!utils::loadConfigs(filename, config))
    {
        cout << "Cannot load config file " << filename << endl;
        return 0;
    }


    const std::string ImgFile = "img_frame_y800.bin";
    HttpClient httpClient;

    HttpClient::GetRequest getRequest =
    {
        .url = "http://10.0.9.78/local/fastcgi_example/example.cgi?:/current-img=y800",
        .fileName = ImgFile,
        .userName = "root",
        .password = "pass"
    };

    httpClient.httpGetRequest(getRequest);

    AxisImg img(ImgFile);
    cout << "Received file " << ImgFile << " (" << img.data().size() << " Bytes)"<< endl;

    const string xmlFileName = "img_frame_y800.xml";
    if (img.saveAsXml(xmlFileName) < 0)
    {
        cout << "Failed to save xml file: " << xmlFileName << endl;
    }
    else
    {
        cout << "Created XML file: " << xmlFileName << endl;
    }

    const HttpClient::PostRequest postRequest =
    {
        .url = "http://127.0.0.1:8080",
        .img = AxisImg(xmlFileName)
    };

    httpClient.httpPostRequest(postRequest);

    return 0;
}
