#pragma once
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef TERMINAL_HANDLER
#define TERMINAL_HANDLER

void make_terminal_editable();
void reset_terminal();

#endif