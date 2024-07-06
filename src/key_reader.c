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
 *      key_reader.c
 */
#include <stdio.h>
#include "include/key_reader.h"

int read_key( const char *file_path, char *key )
{
    FILE *file_key = fopen( file_path, "rb" );
    if ( !file_key )
    {
        perror( "key.txt is missing" );
        return 1;
    }

    fseek( file_key, 0, SEEK_END );
    long size = ftell( file_key );
    rewind( file_key );

    if ( size != 19 )
    {
        perror( "key.txt is not valid" );
        fclose( file_key );
        return 1;
    }

    if ( fread( key, 1, 19, file_key ) != 19 )
    {
        perror( "key.txt could not be read" );
        fclose( file_key );
        return 1;
    }
    key[ 19 ] = '\0';
    fclose( file_key );
    return 0;
}
