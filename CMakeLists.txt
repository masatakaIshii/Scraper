cmake_minimum_required(VERSION 3.14)
project(Scraper C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED True)

set(SRCS
        sources/functions/app.c
        sources/functions/request.c
        sources/functions/config.c
        sources/functions/option.c
        sources/functions/resource.c
        sources/functions/request.c
        sources/functions/session.c
        sources/functions/task.c
        sources/functions/version.c
        sources/functions/common.c
        sources/functions/urlHelper.c
        sources/functions/services/fileExtTypeMime.c
        sources/functions/services/fileNameManager.c
        sources/functions/urlSearcher.c
        sources/functions/lists/listArray.c
        sources/functions/lists/ListChar.c)

set(HEADERS
        sources/headers/app.h
        sources/headers/request.h
        sources/headers/config.h
        sources/headers/option.h
        sources/headers/resource.h
        sources/headers/request.h
        sources/headers/session.h
        sources/headers/task.h
        sources/headers/version.h
        sources/headers/common.h
        sources/headers/urlHelper.h
        sources/headers/services/fileExtTypeMime.h
        sources/headers/services/fileNameManager.h
        sources/headers/urlSearcher.h
        sources/headers/lists/listArray.h
        sources/headers/lists/ListChar.h)

set(TESTSRCS
        test/testShare.c
        test/testDummiesAction.c
        test/testCommon.c
        test/testRequest.c
        test/testRequest.c
        test/testResource.c
        test/testApp.c
        test/testSession.c
        test/testUrlHelper.c
        test/testFileExtTypeMime.c
        test/testFileNameManager.c
        test/testUrlSearcher.c
        test/testPageUrlDummies.c
        test/testListArray.c
        test/testListChar.c)

set(TESTHEADERS
    test/testShare.h
    test/testDummiesAction.h
    test/test.h
    test/testPageUrlDummies.h)

add_executable(Scraper sources/main.c ${SRCS} ${HEADERS})
add_executable(TestScraper test/main.c ${SRCS} ${TESTSRCS} ${HEADERS} ${TESTHEADERS})

file(INSTALL resources/list_file_ext_mime_type.txt DESTINATION ${CMAKE_BINARY_DIR}/)

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
    file(INSTALL test/testPage/testPageNoUrl.html DESTINATION ${CMAKE_BINARY_DIR}/)
    file(INSTALL test/testPage/testPage.html DESTINATION ${CMAKE_BINARY_DIR}/)
    file(INSTALL test/testPage/testPage2.html DESTINATION ${CMAKE_BINARY_DIR}/)
    file(INSTALL test/testPage/testPage4Link.html DESTINATION ${CMAKE_BINARY_DIR}/)
    file(INSTALL test/testPage/testPageTricky.html DESTINATION ${CMAKE_BINARY_DIR}/)
    file(INSTALL test/testPage/testPageSameUrls.html DESTINATION ${CMAKE_BINARY_DIR}/)
else ()
    message("cunit not found")
endif ()