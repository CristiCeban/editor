#pragma once
#include <termios.h>
#include <unistd.h>
#include <stdlib.h>

#ifndef TERMINAL_STATE
#define TERMINAL_STATE

void make_terminal_editable();
void reset_terminal();

#endif