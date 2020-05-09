#include "editor.h"

//Declarations.
fstr *f_str;
const char * error_message = "You should use programm  like this ./editor {file_name}\n";

//Start editor and print the state.
void start_editor(char * filename){
    printf("Program started\n");
    printf("Trying to open %s\n",filename);
    f_str = file_string_open(filename);
    printf("Opened %s with succes",filename);
    start_display(f_str);
}


// Main
int main(int argc, char * argv[]){
    if(argc<2){
        printf("%s",error_message);
        //printf("You should use programm  like this ./editor {file_name}\n");
        return -1;
    }
    // Good case.!!!
    else if(argc==2){
        start_editor(argv[1]);
    }
    else{
        printf("You pushed too much arguments.\n");
        printf("%s",error_message);
        //printf("You should use programm  like this ./editor {file_name}\n");
        return -1;
    }
    return 0;
}