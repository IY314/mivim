#include <ncurses.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "display.h"

#define LN 100
#define BG 101

WINDOW *init(bool *colors) {
    WINDOW *win;

    initscr();

    *colors = has_colors();

    if (*colors) {
        start_color();
    }

    raw();
    noecho();
    refresh();

    win = newwin(LINES, COLS, 0, 0);
    keypad(win, true);
    return win;
}

int main(int argc, char **argv) {
    if (argc != 2) return EXIT_FAILURE;
    String *str = new_stringf(argv[1]);

    bool colors;

    WINDOW *win = init(&colors);

    bool running = true;
    size_t row = 0;
    size_t y = 0;
    size_t x = 0;

    while (running) {
        displayBuffer(str, row, win, &y, &x);

        int ch = wgetch(win);
        switch (ch) {
            case 'q':
                running = false;
                break;
            case KEY_DOWN:
                ++row;
                break;
            case KEY_UP:
                if (row > 0) --row;
                break;
            case 'h':
                if (x > 0) --x;
                break;
            case 'j':
                if (y < (size_t)LINES - 1) ++y;
                break;
            case 'k':
                if (y > 0) --y;
                break;
            case 'l':
                if (x < (size_t)COLS - 1) ++x;
                break;
        }
    }

    endwin();
    del_string(str);
    return EXIT_SUCCESS;
}
