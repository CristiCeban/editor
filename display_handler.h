#pragma once
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdbool.h>
#include "editor.h"
#include "file_handler.h"
#include "terminal_handler.h"
#include "events_handler.h"

#ifndef DISPLAY_HANDLER
#define DISPLAY_HANDLER

struct cursor {
    //pointer to data
    size_t ptr;
    
    // x and y position
    long x,y;
};

struct frame {
    long x,y;
};

void start_display(fstr *f);
void cursor_left();
void cursor_right();
void cursor_down();
void cursor_up();
void render(fstr *f);
void draw(char c);
void insert(fstr *f,char c);
void backspace();
void delete(fstr *f);
void init_display();
void reset_cursor1();
void reset_cursor2();
void calc_cursor_pos(fstr *f);
void calc_frame_shift();
void display_result(fstr *f);
void set_cursor_current();
void clear_rest_screen();
void read_from_keyboard();
#endif