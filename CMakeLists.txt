cmake_minimum_required(VERSION 3.15)
project(sCrapper C)

set(CMAKE_C_STANDARD 99)

add_executable(sCrapper main.c conf_funcs.h conf_funcs.c scrap_funcs.h scrap_funcs.c)

find_package(CURL)
IF (CURL_FOUND)
    include_directories(${CURL_INCLUDE_DIRS})
    target_link_libraries(sCrapper ${CURL_LIBRARIES})
endif()