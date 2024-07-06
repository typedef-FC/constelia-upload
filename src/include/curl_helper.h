/**
 * @title
 *      constelia-upload
 *
 * @author
 *      typedef
 *
 * @description
 *      upload images to API
 *
 * @file
 *      curl_helper.h
 */
#ifndef CONSTELIA_UPLOAD_CURL_HELPER_H
#define CONSTELIA_UPLOAD_CURL_HELPER_H

struct curl_response_information
{
    char *memory;
    size_t size;
};

static size_t write_memory_response( void *contents, size_t size, size_t nmemb, void *userp );

int upload_file( const char *url_base, const char *key, const char *content, long file_size );


#endif //CONSTELIA_UPLOAD_CURL_HELPER_H
