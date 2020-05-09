#pragma once
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <stdbool.h>
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
} cursor;

struct frame {
    long x,y;
} frame;

void start_display(fstr *f);
void cursor_left();
void cursor_right();
void render(fstr *f);
void draw(char c);
void insert(char c);
void init_display();
void reset_cursor();
void calc_cursor_pos(fstr *f);
void calc_frame_shift();
void displayResult(fstr *f);
void set_cursor_current();
#endif