cmake_minimum_required(VERSION 3.5)

project(AxisDataRetriever LANGUAGES CXX)


find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC
    src/main.cpp
    src/AxisImg.cpp
    src/HttpClient.cpp
    src/Utils.cpp)

add_executable(AxisDataRetriever ${SRC})
target_link_libraries(AxisDataRetriever ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
