# /**
#  * @title
#  *      constelia-upload
#  *
#  * @author
#  *      typedef
#  *
#  * @description
#  *      upload images to API
#  *
#  * @file
#  *      CMakeLists.txt
#  */
cmake_minimum_required(VERSION 3.28)


project(constelia-upload C)
set(CMAKE_C_STANDARD 11)

add_executable(constelia-upload src/main.c
        src/include/curl_helper.h
        src/include/key_reader.h
        src/include/file_reader.h
        src/curl_helper.c
        src/key_reader.c
        src/file_reader.c
)

target_link_libraries(constelia-upload curl)