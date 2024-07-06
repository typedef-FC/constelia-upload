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
#include <stdlib.h>
#include <string.h>

#ifdef _WIN32
#include <windows.h>
#else

#include <unistd.h>
#include <limits.h>

#endif

#include "include/key_reader.h"

int get_executable_path( char *buffer, size_t size )
{
#ifdef _WIN32
    if (GetModuleFileName(NULL, buffer, size) == 0) {
        return -1;
    }
#else
    ssize_t len = readlink( "/proc/self/exe", buffer, size - 1 );
    if ( len == -1 )
    {
        return -1;
    }
    buffer[ len ] = '\0';
#endif
    return 0;
}

int read_key( const char *file_path, char *key )
{
    char exec_path[PATH_MAX];
    if ( get_executable_path( exec_path, sizeof( exec_path )) != 0 )
    {
        perror( "Failed to get executable path" );
        return 1;
    }

    // Get directory path from exec_path
    char *last_slash = strrchr( exec_path, '/' );
#ifdef _WIN32
    if (!last_slash) {
        last_slash = strrchr(exec_path, '\\');
    }
#endif
    if ( last_slash )
    {
        *last_slash = '\0'; // Remove the executable name from the path
    }

    // Construct the full path to key.txt
    char key_path[PATH_MAX];
    snprintf( key_path, sizeof( key_path ), "%s/%s", exec_path, file_path );

    FILE *file_key = fopen( key_path, "rb" );
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
