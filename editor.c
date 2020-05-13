#include "editor.h"

//Declarations.
char buffer[buffer_max_size];
char * message;
fstr *f_str;
const char * error_message = "You should use programm  like this ./editor {file_name}\n";

//Start editor and print the state.
void start_editor(char * filename){
    f_str = file_string_open(filename);
    start_display(f_str);
}


// Main
int main(int argc, char * argv[]){
    if(argc<2){
        write(STDIN_FILENO,error_message,strlen(error_message));
        return -1;
    }
    // Good case.!!!
    else if(argc==2){
        message = "Editor started\n";
        snprintf(buffer,strlen(message)+1,message);
        write(STDIN_FILENO,buffer,strlen(buffer));
        start_editor(argv[1]);
        //printf("Press any key to continue...");
        //getchar();
    }
    else{
        char * message = "You pushed too much arguments %d.\n";
        sprintf(buffer,message,argc);
        write(STDOUT_FILENO,buffer,strlen(buffer));
        write(STDOUT_FILENO,error_message,strlen(error_message));
        return -1;
    }
    return 0;
}