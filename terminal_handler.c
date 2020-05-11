#include "terminal_handler.h"

static struct termios trm_before_editing, trm_of_editor ;
void make_terminal_editable(void){
    tcgetattr(STDIN_FILENO, &trm_before_editing);
    trm_of_editor = trm_before_editing;
    trm_of_editor.c_iflag &= ~IXON;
    trm_of_editor.c_lflag &= ~(ECHO | ICANON);
    trm_of_editor.c_cc[VMIN] = 0;
    trm_of_editor.c_cc[VTIME] = 1;
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &trm_of_editor);
    atexit(reset_terminal);
}

void reset_terminal(void){
    tcsetattr(STDIN_FILENO, TCSAFLUSH, &trm_before_editing);
}