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
 *      main.c
 */

#include <stdio.h>
#include <stdlib.h>

#include "include/curl_helper.h"
#include "include/key_reader.h"
#include "include/file_reader.h"

int main( int argc, char **argv )
{
    /**
     * let's check arguments now.
     * constelia-upload <file_path>
     */
    if ( argc != 2 )
    {
        fprintf( stderr, "Usage: constelia-upload <file_path>\n" );
        return 1;
    }

    char key[20];
    if ( read_key( "key.txt", key ) != 0 )
    {
        return 1;
    }

    char *content;
    long file_size;
    if ( read_file( argv[ 1 ], &content, &file_size ) != 0 )
    {
        return 1;
    }

    /**
     * output some debug information and prepare cURL
     * we're going to send a normal API request as you would with anything else.
     * nothing fancy about this.
     */
    printf( "key: %s\n", key );
    printf( "file: %ld bytes read from %s\n", file_size, argv[ 1 ] );

    if ( upload_file( "https://constelia.ai/api.php", key, content, file_size ) != 0 )
    {
        free( content );
        return 1;
    }

    /**
     * cleaning up
     */
    free( content );
    return 0;
}
