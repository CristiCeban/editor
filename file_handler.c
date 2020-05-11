#include "file_handler.h"
#include "events_handler.h"

fstr* file_string_open(char * filename){

    // Allocate new file_string and 
    fstr *f = malloc(sizeof(fstr));
    f->filename = filename;

    // Open file, if it's not created it will create it;
    FILE * file ;
    file = fopen(filename,"ab+");
    if(file == NULL)
        die("File could not be opened");

    // Get the size of the file.
    fseek(file,0,SEEK_END);
    f->size = ftell(file);

    // Reset the cursor of the fseek;
    fseek(file,0,SEEK_SET);
    
    
    // Print the size of the file.
    //printf("The size is :%ld\n",f->size);
    
    // Alocate the size of the file_data to store file's data.
    // TODO sa ma uit daca tot e bine.
    
    //f->file_data = malloc(sizeof(char)*f->size);
    f->file_data = malloc(f->size);

    // Read the data from file and store them in file_data.
    for(size_t iter = 0; iter < f->size; iter++)
        f->file_data[iter] = fgetc(file);

    // Close file;
    fclose(file);

    // Return the file_string with data from file and it's size.
    return f;
}

// Close file_string, Free memory.
void file_string_close(fstr *f){
    free(f->file_data);
    free(f);
}

// Write the data to the file.
void file_string_write(fstr *f){
    // Open the file in which data will be writen.
    FILE *file = fopen(f->filename,"w+");
    
    // If file could be open throw a error.
    if (file==NULL)
        die("File could not be open");
    
    // Write the data from file_string->file_data to file.
    for(size_t iter=0; iter< f->size; iter++){
        fputc(f->file_data[iter],file);
    }
    
    // Close file.
    fclose(file);
}

// Append to the file_string
void file_string_append(fstr *f, char c){
    f->file_data = realloc(f->file_data,f->size +1);
    f->file_data[f->size] = c;
    f->size++;
}

//insert char at given index into file_string
void file_string_insert_char(fstr *f,char c,size_t i){
    f->file_data = realloc(f->file_data,f->size+1);
    memcpy(f->file_data +i+1,f->file_data +i,f->size-i);
    f->file_data[i] = c;
    f->size++;
}
//delete char at index i from file_string
void file_string_remove_char(fstr *f,size_t i){
    //char * new_data = malloc(sizeof(char)*f->size-1);
    char * new_data = malloc(f->size-1);
    memcpy(new_data, f->file_data,i);
    memcpy(new_data + i,f->file_data+i+1,f->size - i - 1);
    free(f->file_data);
    f->file_data = new_data;
    f->size--;
}
// Get char at index i from file_string
char file_string_get_char(fstr *f,size_t i){
    return f->file_data[i];
}

//Get the size of the file_string
size_t file_string_get_size(fstr *f) {
    return f->size;
}