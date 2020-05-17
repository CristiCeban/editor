#include "display_handler.h"


//Definitions 

char * message;
char buffer[buffer_max_size];
// Terminal dimensions.
struct winsize terminal_dimensions;

// Cursor position (x,y);
struct cursor cur;
// Frame position (x,y);
struct frame frm;
size_t p = 0;
long x=0,y = 0, margin = 2;

// Special for future;
enum Mode mode = NORMAL;



// Functions..


void mode_normal(fstr *f){
    clear_screen();
    reset_cursor2();
    cursor_down(f);
    mode=NORMAL;
    write(STDOUT_FILENO,"MODE NORMAL\n",11);
}

void mode_insertion(fstr *f){
    clear_screen();
    reset_cursor2();
    cursor_down(f);
    mode=INSERTION;
    write(STDOUT_FILENO,"MODE INSERTIO\n",15);
}
// Reset cursor.
void reset_cursor1(){
    if(cur.x>0){
        message = "\033[%ldD";
        sprintf(buffer,message,cur.x);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }
    if(cur.y - frm.y > 0){
        message = "\033[%ldA";
        sprintf(buffer,message,cur.y-frm.y);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }
}


//Set the cursor down.
void set_cursor_down(){
    message = "\033[%ldD";
    sprintf(buffer,message,terminal_dimensions.ws_col);
    write(STDOUT_FILENO,buffer,strlen(buffer));
    message = "\033[%ldA";
    sprintf(buffer,message,terminal_dimensions.ws_row);
    write(STDOUT_FILENO,buffer,strlen(buffer));
}
//Reset cursor 2
void reset_cursor2(){
    if (x > 0){
        message = "\033[%ldD";
        sprintf(buffer,message,x);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }
    if (y > 0){
        message = "\033[%ldA";
        sprintf(buffer,message,y);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }
        
}

// Move cursor to the left.
void cursor_left() {
    if(cur.ptr > 0)
        cur.ptr--;
}

// Move cursor to the right.
void cursor_right(fstr *f) {
    if (cur.ptr < file_string_get_size(f))
        cur.ptr++;
}

//Move cursor down.
void cursor_down(fstr *f){
    while(cur.ptr < file_string_get_size(f) &&
        file_string_get_char(f,cur.ptr) != '\n')
            cur.ptr++;
    if(cur.ptr < file_string_get_size(f))
        cur.ptr++;
    long x = 0;
    while(cur.ptr <file_string_get_size(f) &&
        file_string_get_char(f,cur.ptr) != '\n' &&
        x < cur.x){
            cur.ptr++;
            x++;
        }    
}

//Move cursor up
void cursor_up(fstr *f){
    if(cur.y > 0){
        cur.ptr--;
        while(file_string_get_char(f,cur.ptr)!='\n')
            cur.ptr--;
        cur.ptr--;
        long size = 1;
        while(cur.ptr > 0 && file_string_get_char(f,cur.ptr)!='\n'){
            cur.ptr--;
            size++;
        }
        if(cur.x > size) 
            cur.ptr += size;
        else cur.ptr += cur.x+1; // TODO CHECK IF +cur.x or +cur.x+1;
    }
    else
        cur.ptr = 0;
}
// Calculate the cursor possition at the begining.
void calc_cursor_pos(fstr *f){
    // Definitions.
    p = 0 ; x=0 ; y = 0;
    // Calculate the positions of the cursor.(X,Y);
    while(p < cur.ptr){
        if (file_string_get_char(f,p) == '\n'){
            x = 0;
            y ++;
        }
        else if(file_string_get_char(f,p) == '\t')
            x+=4;
        else 
            x++;
        p++;
    }
    cur.x = x;
    cur.y = y;
}


// Calculate the frame shift. (default is 2).
void calc_frame_shift(){
    margin = 2;
    if(cur.x - terminal_dimensions.ws_col + margin > 0)
        frm.x =cur.x - terminal_dimensions.ws_col + margin;
    else frm.x = 0;
    if (cur.y - terminal_dimensions.ws_row + margin > 0)
        frm.y = cur.y - terminal_dimensions.ws_row + margin;
    else frm.y = 0;
}


void backspace(fstr *f){
    if(cur.ptr > 0) {
        file_string_remove_char(f,cur.ptr-1);
        cur.ptr--;
    }
}

void delete(fstr *f){
    if(cur.ptr >= 0 && cur.ptr < file_string_get_size(f)){
        file_string_remove_char(f,cur.ptr);
    }
}

void insert(fstr *f,char c){
    if(cur.ptr == file_string_get_size(f))
        file_string_append(f,c);
    else
        file_string_insert_char(f,c,cur.ptr);
    cur.ptr++;
}
// Draw character.
// TODO add higlight.
void draw(char c){
    // For example number,symbols,key words.
    if ((c >= '0' && c <= '9') || 
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '.')               ){
            message = "%c";
            sprintf(buffer,message,c);
            write(STDOUT_FILENO,buffer,strlen(buffer));
        }
    else if (c == ' ') {
        message = " ";
        sprintf(buffer,message);
        write(STDOUT_FILENO,buffer,strlen(buffer));
        }
    // This one is for handling color for future...
    else {
        message = "%c";
        sprintf(buffer,message,c);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }

}

//Display the result of the file_string.
void display_result(fstr *f){

    //Declarations
    p = 0; x = 0; y = 0;
    //pass throught non-value(visible)
    while(y<frm.y){
        if(file_string_get_char(f,p) == '\n')
            y++;
        p++;
    }
    
    //draw the value
    while(p < file_string_get_size(f) && y <= frm.y + terminal_dimensions.ws_row - margin){
        if(file_string_get_char(f,p) == '\n'){
            message = "\033[K\n";
            sprintf(buffer,message);
            write(STDOUT_FILENO,buffer,strlen(buffer));
            y++;
            x = 0;
        }
        else if(file_string_get_char(f,p) == '\t'){
            message = "    ";
            sprintf(buffer,message);
            write(STDOUT_FILENO,buffer,strlen(buffer));
            x+=4;
        }
        else {
            if(x >= frm.x && x < frm.x + terminal_dimensions.ws_col)
                draw(file_string_get_char(f,p));
            x ++;
        }
        p ++;
    }

}

//Clear all the screen;
void clear_screen(){
    message = "\033[0m\033[K";
    sprintf(buffer,message);
    write(STDOUT_FILENO,buffer,strlen(buffer));
    for(int y = 0;y < terminal_dimensions.ws_row;y++){
        message = "\033[K\n";
        sprintf(buffer,message);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }
}

//Clear the rest of the screen
void clear_rest_screen(){
     // Clear the rest of the screen.
    message = "\033[0m\033[K";
    sprintf(buffer,message);
    write(STDOUT_FILENO,buffer,strlen(buffer));
    while (y <= frm.y + terminal_dimensions.ws_row - margin) {
        message = "\033[K\n";
        sprintf(buffer,message);
        write(STDOUT_FILENO,buffer,strlen(buffer));
        y++;
    }   
}

//Init display.
void init_display(){
    frm.x = 0;frm.y = 0;cur.x = 0;cur.y = 0;cur.ptr = 0;
}

void set_cursor_current(){
    if (cur.x - frm.x > 0){
        message = "\033[%ldC";
        sprintf(buffer,message, cur.x - frm.x);
        write(STDOUT_FILENO,buffer,strlen(buffer));

    }
    if (cur.y - frm.y > 0){
        message = "\033[%ldB";
        sprintf(buffer,message,cur.y - frm.y);
        write(STDOUT_FILENO,buffer,strlen(buffer));
    }
        

}

//Read user input
void read_from_keyboard(fstr *f){
    char c;
    while(true){
        if(!read(STDIN_FILENO,&c,1))
            continue;

        //CTRL-s
        else if(c == 19){
            file_string_write(f);
            break;
        }

        //escape character.(Special char).
        else if (c == 27) {

            if(read(STDIN_FILENO,&c,1)){
                //CTRL character
                if(c == '['){
                    read(STDIN_FILENO,&c,1);

                    //arrows keys
                    if(c == 'A')
                        //TODO UP
                        cursor_up(f);
                    else if(c == 'B')
                        //TODO DOWN
                        cursor_down(f);
                    else if(c == 'C')
                        cursor_right(f);
                    else if (c == 'D')
                        cursor_left();
                    
                    //delete
                    else if( c == '3'){
                        read(STDIN_FILENO,&c,1);
                        if (c=='~'){
                            delete(f);
                        }
                    }

                }
            }

            //escape Key.
            //else if(mode==INSERTION)
                //mode_normal(f);
            //else break;
        }

        // backspace 
        else if (c == 127){
            if (cur.ptr > 0)
                backspace(f);
        }
        else if(mode == NORMAL && c == 105){
            //mode_insertion(f);
        }
        //char
        else {
            if(c==13)
                c = '\n';
            insert(f,c);
        }
        render(f);
    }
}

void set_pos_end(fstr *f){
    cur.ptr = file_string_get_size(f);
    render(f);
    message = "\n";
    sprintf(buffer,message);
    write(STDOUT_FILENO,buffer,strlen(buffer));
    file_string_close(f);
}

//Render
void render(fstr *f){
    // Read terminal dimensions.
    ioctl(STDOUT_FILENO,TIOCGWINSZ, &terminal_dimensions);
    
    // Reset cursor 1
    reset_cursor1();

    //Calculate cursor x and y coordinates.
    calc_cursor_pos(f);
    
    //Calculate frame shift.
    calc_frame_shift();

    //Display result;
    display_result(f);

    //clear rest of the screen
    clear_rest_screen();
    //RESET NORMAL CURSOR WITH X AND Y
    // Reset Cursor.2
    reset_cursor2();

    //Set the cursor to backspace();curent character.
    set_cursor_current();
    

    //display the results.
    //fflush(stdout);
}

void start_display(fstr *f){
    //Init Display.(display_hander.h);
    init_display();

    //Make terminal editable(terminal_handler.h);
    make_terminal_editable();

    //Render (display_hander.h);
    render(f);

    //Read the user input
    read_from_keyboard(f); 

    //Set pos to the end.
    set_pos_end(f);

    //Reset terminal
    reset_terminal();
}

