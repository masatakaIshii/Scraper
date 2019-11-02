cmake_minimum_required(VERSION 3.14)
project(Scraper C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SRCS
    sources/app.c
    sources/request.c
    sources/config.c
    sources/option.c
    sources/resource.c
    sources/request.c
    sources/session.c
    sources/task.c
    sources/version.c
    sources/common.c
    sources/urlHelper.c)

set(HEADERS
    sources/app.h
    sources/request.h
    sources/config.h
    sources/option.h
    sources/resource.h
    sources/request.h
    sources/session.h
    sources/task.h
    sources/version.h
    sources/common.h
    sources/urlHelper.h)

set(TESTSRCS
    test/testDummiesAction.c
    test/testCommon.c
    test/testRequest.c
    test/testRequest.c
    test/testResource.c
    test/testApp.c
    test/testSession.c
    test/testUrlHelper.c)

set(TESTHEADERS
    test/testDummiesAction.h
    test/test.h)

add_executable(Scraper sources/main.c ${SRCS} ${HEADERS})
add_executable(TestScraper test/main.c ${SRCS} ${TESTSRCS} ${HEADERS} ${TESTHEADERS})

if (${CMAKE_BUILD_TYPE} STREQUAL "Release")
    file(INSTALL ${CMAKE_BINARY_DIR}/Scraper.exe DESTINATION ../bin)
endif ()


find_package(CURL)
if (CURL_FOUND)
    message("Curl found")
    target_include_directories(Scraper PUBLIC ${CURL_INCLUDE_DIRS})
    target_include_directories(TestScraper PUBLIC ${CURL_INCLUDE_DIRS})
    target_link_libraries(Scraper PUBLIC ${CURL_LIBRARIES})
    target_link_libraries(TestScraper PUBLIC ${CURL_LIBRARIES})
else ()
    message(Curl not found)
endif ()

find_package(PkgConfig REQUIRED)

pkg_check_modules(CUNIT REQUIRED cunit)
if (CUNIT_FOUND)
    message("Cunit found")
    target_include_directories(TestScraper PUBLIC ${CUNIT_INCLUDE_DIRS})
    target_link_libraries(TestScraper PUBLIC ${CUNIT_LIBRARIES})
else ()
    message("cunit not found")
endif ()