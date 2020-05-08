#include "terminal_state.h"
#include "file_handler.h"
#include <stdio.h>
#include <stdbool.h>


void start_editor(char * filename){
    printf("Program started\n");
    printf("Trying to open %s\n",filename);
    file_string_open(filename);
    while(true){
        make_terminal_editable();   
    }
}
int main(int argc, char * argv[]){
    if(argc<2){
        printf("You should use programm  like this ./editor {file_name}\n");
        return -1;
    }
    else if(argc==2){
        start_editor(argv[1]);
    }
    return 0;
}