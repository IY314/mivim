#pragma once

#include <ncurses.h>

#include "dynstr.h"

void displayBuffer(String *buff, size_t row, WINDOW *win, size_t *y, size_t *x);
