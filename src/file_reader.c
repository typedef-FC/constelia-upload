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
 *      file_reader.c
 */
#include <stdio.h>
#include <stdlib.h>
#include "include/file_reader.h"

int read_file( const char *file_path, char **content, long *file_size )
{
    FILE *file = fopen( file_path, "rb" );
    if ( !file )
    {
        perror( "file is not accessible" );
        return 1;
    }

    fseek( file, 0, SEEK_END );
    *file_size = ftell( file );
    rewind( file );

    *content = ( char * ) malloc( *file_size );
    if ( !*content )
    {
        perror( "failed to allocate memory" );
        fclose( file );
        return 1;
    }

    if ( fread( *content, 1, *file_size, file ) != *file_size )
    {
        perror( "file could not be read" );
        free( *content );
        fclose( file );
        return 1;
    }
    fclose( file );
    return 0;
}
