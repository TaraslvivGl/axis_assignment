#include "Utils.h"

#include <vector>

namespace utils
{
    std::string encodeBase64(const std::string& in)
    {
        std::string out;
        int val = 0, valb = -6;
        size_t len = in.length();
        for (size_t i = 0; i < len; ++i)
        {
            unsigned char c = in[i];
            val = (val<<8) + c;
            valb += 8;
            while (valb >= 0)
            {
                out.push_back(Base64UrlAlphabet[(val>>valb)&0x3F]);
                valb -= 6;
            }
        }
        if (valb > -6)
        {
            out.push_back(Base64UrlAlphabet[((val<<8)>>(valb+8))&0x3F]);
        }

        return out;
    }

    std::string decodeBase64(const std::string & in)
    {
        std::string out;
        std::vector<int> T(256, -1);
        for (size_t i =0; i < 64; ++i)
        {
            T[Base64UrlAlphabet[i]] = i;
        }

        int val = 0, valb = -8;
        for (size_t i = 0; i < in.length(); ++i)
        {
            unsigned char c = in[i];
            if (T[c] == -1)
            {
                break;
            }
            val = (val<<6) + T[c];
            valb += 6;
            if (valb >= 0)
            {
                out.push_back(char((val>>valb)&0xFF));
                valb -= 8;
            }
      }
      return out;
    }

    bool testBase64(const std::string& testString)
    {
        const std::string encodedtestString = encodeBase64(testString);
        return decodeBase64(encodedtestString) == testString;
    }

    void getValueByTag(xmlNodePtr node, const char* tagName, std::string& value)
    {
        for (xmlNodePtr child = node; child != NULL; child = child->next)
        {
            if (child->type == XML_ELEMENT_NODE)
            {
                if (xmlStrcmp(child->name, reinterpret_cast<const xmlChar*>(tagName)) == 0)
                {
                    xmlChar* content = xmlNodeGetContent(child);
                    value = reinterpret_cast<const char*>(content);
                    xmlFree(content);

                    return;
                }

                // Recursively search child nodes
                getValueByTag(child->children, tagName, value);
            }
        }
        return;
    }

    bool loadConfigs(const std::string& xmlConfig, Configs& configs)
    {
        if (!std::filesystem::exists(xmlConfig))
        {
            std::cout << xmlConfig << " not found" << std::endl;
            return false;
        }

        const char* axisUrl = "axis-url";
        const char* userName = "user-name";
        const char* userPassword = "user-password";
        const char* httpServerUrl = "http-server-url";
        const char* outBinFile = "out-bin-file";
        const char* outXmlFile = "out-xml-file";

        LIBXML_TEST_VERSION;

        xmlDocPtr doc = xmlReadFile(xmlConfig.c_str(), NULL, 0);

        if (doc == NULL) {
            std::cout << "Error reading the XML file." << std::endl;
            return false;
        }

        xmlNodePtr root = xmlDocGetRootElement(doc);

        getValueByTag(root, axisUrl, configs.axisCgiUrl);
        getValueByTag(root, userName, configs.userName);
        getValueByTag(root, userPassword, configs.password);
        getValueByTag(root, httpServerUrl, configs.httpServerUrl);
        getValueByTag(root, outBinFile, configs.outBinFile);
        getValueByTag(root, outXmlFile, configs.outXmlFile);

        std::cout << std::endl;
        std::cout << "Loaded configs from " << xmlConfig << ":" << std::endl;
        std::cout <<"------------------------------"<< std::endl;
        std::cout << configs.axisCgiUrl << std::endl;
        std::cout << configs.userName << std::endl;
        std::cout << configs.password << std::endl;
        std::cout << configs.httpServerUrl << std::endl;
        std::cout << configs.outBinFile << std::endl;
        std::cout << configs.outXmlFile << std::endl;

        xmlFreeDoc(doc);
        xmlCleanupParser();
        std::cout << xmlConfig << std::endl <<"------------------------------"<< std::endl;

        return true;
    }
}
