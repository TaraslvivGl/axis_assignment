cmake_minimum_required(VERSION 3.5)

project(AxisDataRetriever LANGUAGES CXX)


find_package(CURL REQUIRED)
include_directories(${CURL_INCLUDE_DIR})

find_package(LibXml2 REQUIRED)
include_directories(${LIBXML2_INCLUDE_DIR})

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AxisDataRetriever main.cpp AxisImg.cpp HttpClient.cpp Utils.cpp)
target_link_libraries(AxisDataRetriever ${CURL_LIBRARIES} ${LIBXML2_LIBRARIES})
