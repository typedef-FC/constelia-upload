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
 *      curl_helper.c
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include "include/curl_helper.h"

static size_t write_memory_response( void *contents, size_t size, size_t nmemb, void *userp )
{
    size_t realsize = size * nmemb;
    struct curl_response_information *mem = ( struct curl_response_information * ) userp;

    char *ptr = realloc( mem->memory, mem->size + realsize + 1 );
    if ( ptr == NULL)
    {
        fprintf( stderr, "not enough memory (realloc returned NULL)\n" );
        return 0;
    }

    mem->memory = ptr;
    memcpy( &( mem->memory[ mem->size ] ), contents, realsize );
    mem->size += realsize;
    mem->memory[ mem->size ] = 0; // Null terminate

    return realsize;
}

int upload_file( const char *url_base, const char *key, const char *content, long file_size )
{
    CURL *curl;
    CURLcode response = CURLE_TOO_LARGE;

    struct curl_response_information data;
    data.memory = malloc( 1 ); // Initial allocation
    data.size = 0;

    curl_global_init(CURL_GLOBAL_DEFAULT);
    curl = curl_easy_init( );
    if ( curl )
    {
        char url[256];
        snprintf( url, sizeof( url ), "%s?key=%s&cmd=upload", url_base, key );

        curl_easy_setopt( curl, CURLOPT_URL, url );
        curl_easy_setopt( curl, CURLOPT_POSTFIELDS, content );
        curl_easy_setopt( curl, CURLOPT_POSTFIELDSIZE, file_size );

        curl_easy_setopt( curl, CURLOPT_WRITEFUNCTION, write_memory_response );
        curl_easy_setopt( curl, CURLOPT_WRITEDATA, ( void * ) &data );

        response = curl_easy_perform( curl );
        if ( response != CURLE_OK )
        {
            fprintf( stderr, "curl_easy_perform() failed: %s\n", curl_easy_strerror( response ));
        }
        else
        {
            printf( "url: %s\n", data.memory );

            /**
             * show output/url in console/terminal
             * finally, we can copy the URL to clipboard
             *
             * we're going to do both xclip and wl-copy for linux users.
             * save our time from checking extra stuff. nothing bad will happen if we use both.
             * one of them is going to say it's not recognized anyway
             */
            char cb_buffer[512];

#ifdef __linux__
            snprintf( cb_buffer, sizeof( cb_buffer ), "echo '%s' | xclip -selection clipboard", data.memory );
            system( cb_buffer );

            snprintf( cb_buffer, sizeof( cb_buffer ), "echo '%s' | wl-copy", data.memory );
            system( cb_buffer );
#else
            snprintf(cb_buffer, sizeof(cb_buffer), "echo %s | clip", data.memory);
            system(cb_buffer);
#endif
            printf( "response copied to clipboard.\n" );
        }

        curl_easy_cleanup( curl );
    }

    curl_global_cleanup( );
    free( data.memory );
    return ( response == CURLE_OK ) ? 0 : 1;
}
