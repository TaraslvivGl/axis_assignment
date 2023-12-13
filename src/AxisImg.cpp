#include "AxisImg.h"
#include "Utils.h"

AxisImg::AxisImg(const std::string fileName):
    m_fileName(fileName){}

std::string AxisImg::data() const
{
    std::ifstream img(m_fileName, std::ios::binary);
    std::string buffer;

    if (img.is_open())
    {
        const std::uintmax_t FileSize = std::filesystem::file_size(m_fileName);
        buffer.resize(FileSize);
        img.read(buffer.data(), FileSize);
        img.close();
    }
    else
    {
        std::cout << "Failed to open file " << m_fileName << std::endl;
    }

    return buffer;
}

std::string AxisImg::dataBase64() const
{
    return utils::encodeBase64(data());
}

int AxisImg::saveAsXml(const std::string &xmlFileName) const
{
    xmlDocPtr doc = xmlNewDoc(BAD_CAST "1.0");
    xmlNodePtr root = xmlNewNode(NULL, BAD_CAST "ImageData");
    xmlDocSetRootElement(doc, root);

    struct stat fileInfo;
    if (stat(m_fileName.c_str(), &fileInfo) == 0)
    {
        xmlNodePtr timetamp = xmlNewNode(NULL, BAD_CAST "Timestamp");
        xmlNodePtr dateTime = xmlNewNode(NULL, BAD_CAST "DateTime");

        const auto timestamp = std::to_string(static_cast<int>(fileInfo.st_ctime));
        xmlNodeAddContent(timetamp, BAD_CAST timestamp.c_str());

        char timeBuffer[50];
        const char timeFormat[] = "%Y-%m-%d %H:%M:%S%Z";
        std::tm* time = std::gmtime(&fileInfo.st_ctime);
        std::strftime(timeBuffer, sizeof(timeBuffer), timeFormat, time);
        xmlNodeAddContent(dateTime, BAD_CAST timeBuffer);

        xmlAddChild(root, timetamp);
        xmlAddChild(root, dateTime);
    }
    else
    {
        std::cout << "Failed to get file time creation." << std::endl;
    }

    xmlNodePtr imageBase64 = xmlNewNode(NULL, BAD_CAST "ImageBase64");
    xmlNodeAddContent(imageBase64, BAD_CAST dataBase64().c_str());
    xmlAddChild(root, imageBase64);

    const int Spaces = 5;
    const int res = xmlSaveFormatFileEnc(xmlFileName.c_str(), doc, "UTF-8", Spaces);

    xmlFreeDoc(doc);
    xmlCleanupParser();
    return res;
}
