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
 *      file_reader.h
 */

#ifndef CONSTELIA_UPLOAD_FILE_READER_H
#define CONSTELIA_UPLOAD_FILE_READER_H

int read_file( const char *file_path, char **content, long *file_size );

#endif //CONSTELIA_UPLOAD_FILE_READER_H
