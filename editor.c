#include "editor.h"

fstr *f_str;
void start_editor(char * filename){
    printf("Program started\n");
    printf("Trying to open %s\n",filename);
    f_str = file_string_open(filename);
    printf("Opened %s with succes",filename);
    make_terminal_editable();
    printf_file(f_str);   
    while(true){
        
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
    else{
        printf("You pushed too much arguments.\n");
        printf("You should use programm  like this ./editor {file_name}\n");
        return -1;
    }
    return 0;
}