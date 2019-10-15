cmake_minimum_required(VERSION 3.14)

project(scraper)

set(CMAKE_C_STANDARD 99)

add_executable(scraper main.c)

find_package(CURL)
if(CURL_FOUND)
    message(Curl found)
    target_include_directories(scraper PUBLIC ${CURL_INCLUDE_DIRS})
    target_link_libraries(scraper PUBLIC ${CURL_LIBRARIES})
else()
    message(Curl not found)
endif()

