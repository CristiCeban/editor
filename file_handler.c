#include "file_handler.h"

fstr* file_string_open(char * filename){

    // Allocate new file_string and 
    fstr *f = malloc(sizeof(fstr));
    f->filename = filename;

    // Open file, if it's not created it will create it;
    FILE * file ;
    file = fopen(filename,"ab+");
    if(file == NULL){
        exit(-1);
    }
    return f;
}

// Close file_string.
void file_string_close(fstr *f){
    free(f->file_data);
    free(f);
}