#ifndef UTILS_H
#define UTILS_H

#include <string>
#include <libxml/parser.h>
#include <libxml/tree.h>
#include <iostream>
#include <filesystem>

namespace utils
{
    const char Base64UrlAlphabet[] = {
        'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J', 'K', 'L', 'M',
        'N', 'O', 'P', 'Q', 'R', 'S', 'T', 'U', 'V', 'W', 'X', 'Y', 'Z',
        'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm',
        'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 'x', 'y', 'z',
        '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '-', '_'
    };

    struct Configs
    {
        std::string axisCgiUrl;
        std::string userName;
        std::string password;
        std::string outBinFile;
        std::string outXmlFile;
        std::string httpServerUrl;
    };

    std::string encodeBase64(const std::string& in);
    std::string dencodeBase64(const std::string& in);
    bool testBase64(const std::string& testString);
    void getValueByTag(xmlNodePtr node, const char* tagName, std::string& value);
    bool loadConfigs(const std::string& xmlConfig, Configs& configs);
}

#endif // UTILS_H
