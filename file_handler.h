#pragma once
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#ifndef FILE_HANDLER
#define FILE_HANDLER


// file string
typedef struct file_string{
    char * file_data;
    size_t size;
    char *filename;
} fstr;

// Create a new file_string.
fstr * file_string_open(char * filename);

// close file_string.
void file_string_close(fstr *f);
#endif