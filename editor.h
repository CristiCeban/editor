#pragma once
#include <stdio.h>
#include <stdbool.h>
#include "terminal_handler.h"
#include "file_handler.h"
#include "display_handler.h"
#ifndef EDITOR
#define EDITOR
#define buffer_max_size 256
void start_editor(char * filename);

#endif
