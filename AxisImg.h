#ifndef AXISIMG_H
#define AXISIMG_H

#include <string>
#include <iostream>
#include <stdio.h>
#include <filesystem>
#include <fstream>
#include <vector>

//#include <libxml/parser.h>
#include <libxml/tree.h>
#include <sys/stat.h>

class AxisImg
{
public:
    AxisImg(const std::string fileName);
    AxisImg(const AxisImg&) = default;
    AxisImg& operator=(const AxisImg& img)
    {
        m_fileName = img.m_fileName;
        return *this;
    }

    std::string data() const;
    std::string dataBase64() const;
    int saveAsXml(const std::string& xmlFileName) const;


private:
    std::string m_fileName;
};

#endif // AXISIMG_H
