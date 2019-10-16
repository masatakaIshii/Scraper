cmake_minimum_required(VERSION 3.14)
project(Scraper C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SRCS
    sources/request.c
    sources/config.c)

set(HEADERS
    sources/request.h)

add_executable(Scraper sources/main.c ${SRCS} ${HEADERS})
#add_executable(Scraper test/main.c ${SRCS} ${HEADERS})

find_package(CURL)
if (CURL_FOUND)
    message("Curl found")
    target_include_directories(Scraper PUBLIC ${CURL_INCLUDE_DIRS})
    target_link_libraries(Scraper PUBLIC ${CURL_LIBRARIES})
else ()
    message(Curl not found)
endif ()

find_package(PkgConfig REQUIRED)

pkg_check_modules(CUNIT REQUIRED cunit)
if (CUNIT_FOUND)
    message("Cunit found")
    target_include_directories(Scraper PUBLIC ${CUNIT_INCLUDE_DIRS})
    target_link_libraries(Scraper PUBLIC ${CUNIT_LIBRARIES})
else ()
    message("cunit not found")
endif ()