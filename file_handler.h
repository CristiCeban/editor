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

// Print the data from file_string;
void printf_file(fstr *f);

// Write the data to file;
void file_string_write(fstr *f);

// Get char at index i from file_string
char file_string_get_char(fstr *f,size_t i);

// Get the size of the file_string.
size_t file_string_get_size(fstr *f);
#endif