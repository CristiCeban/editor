#include "display_handler.h"

// Terminal dimensions.
struct winsize terminal_dimensions;

// Cursor position (x,y);
struct cursor cur;
// Frame position (x,y);
struct cursor frm;

// Reset cursor.
void reset_cursor(){
    if(cur.x>0)
        printf("\033[%ldD", cur.x);
    if(cur.y - frm.y > 0)
        printf("\033[%ldA", cur.y - frm.y);
}
// Move cursor to the left.
void cursor_left() {
    if(cur.ptr > 0)
        cur.ptr--;
}

// Move cursor to the right.
void cursor_right(fstr *f) {
    if (cur.ptr < file_string_get_size(f))
        cur.ptr ++;
}

// Calculate the cursor possition at the begining.
void calc_cursor_pos(fstr *f){
    // Definitions.
    size_t p = 0;
    long x,y = 0;
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
        p +=1;
    }
    cur.x = x;
    cur.y = y;
}


// Calculate the frame shift. (default is 2).
void calc_frame_shift(){
    long margin = 2;
    if(cur.x - terminal_dimensions.ws_col + margin > 0)
        frm.x =cur.x - terminal_dimensions.ws_col + margin;
    else frm.x = 0;
    if (cur.y - terminal_dimensions.ws_row + margin > 0)
        frm.y = cur.y - terminal_dimensions.ws_row + margin;
    else frm.y = 0;
}

// Draw character.
// TODO add higlight.
void draw(char c){
    //TODO make highlight with color.
    // For example number,symbols,key words.
    if ((c >= '0' && c <= '9') || 
        (c >= 'a' && c <= 'z') ||
        (c >= 'A' && c <= 'Z') ||
        (c == '.')               )
        printf("%c",c);
    else if (c == ' ') printf(" ");
    else {
        printf("%c",c);
    }

}

//Display the result of the file_string.
void displayResult(fstr *f){

    size_t p = 0; long x,y = 0;
    int margin = 2;
    while(p < file_string_get_size(f) && y <= frm.y + terminal_dimensions.ws_row - margin){
        if(file_string_get_char(f,p) == '\n'){
            y++;
            x = 0;
        }
        else {
            if(x >= frm.x && x < frm.x + terminal_dimensions.ws_col)
                draw(file_string_get_char(f,p));
            x ++;
        }
        p ++;
    }

    // Clear the rest of the screen.
    printf("\033[0m\033[K");
    while (y <= frm.y + terminal_dimensions.ws_row - margin) {
    printf("\033[K\n");
    y += 1;
    }   

}

//Init display.
void init_display(){
    frm.x=frm.y=cur.x=cur.y=cur.ptr=0;
}

void set_cursor_current(){
    if (cur.x - frm.x > 0)
        printf("\033[%ldC", cur.x - frm.x);
    if (cur.y - frm.y > 0)
        printf("\033[%ldB", cur.y - frm.y);

}
void render(fstr *f){
    // Read terminal dimensions.
    ioctl(STDOUT_FILENO,TIOCGWINSZ, &terminal_dimensions);
    
    // Reset cursor
    reset_cursor();

    //Calculate cursor x and y coordinates.
    calc_cursor_pos(f);
    
    //Calculate frame shift.
    calc_frame_shift();

    //Display result;
    displayResult(f);

    // Reset Cursor.
    reset_cursor();

    //Set the cursor to curent character.
    set_cursor_current();
    
    // printf_file(f);

    //display the results.
    fflush(stdout);
}

void start_display(fstr *f){
    //Init Display.(display_hander.h);
    init_display();

    //Make terminal editable(terminal_handler.h);
    make_terminal_editable();

    //Render (display_hander.h);
    render(f);

    //TODO get the char from input.
    while(true){}
}