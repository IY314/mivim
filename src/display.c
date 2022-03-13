#include "display.h"

size_t numPlaces(size_t n) {
    size_t r = 1;
    if (n < 0) n = (n == 0) ? SIZE_MAX : -n;
    while (n > 9) {
        n /= 10;
        r++;
    }
    return r;
}

size_t countLines(String *buff) {
    if (buff == NULL) return 0;
    size_t lines = 0;

    for (size_t i = 0; i < buff->len; ++i)
        if (str_at(buff, i) == '\n') ++lines;

    return lines;
}

void displayBuffer(String *buff, size_t row, WINDOW *win, size_t *y,
                   size_t *x) {
    if (buff == NULL || win == NULL) return;
    wclear(win);
    wrefresh(win);

    // get line number padding size
    size_t maxLineNumLen = numPlaces(countLines(buff));

    // init vars for waddch, lineCount is for true lines while lines is for
    // position (line wrapping)
    size_t lineCount = 0;
    size_t lines = 0;
    size_t cols = 0;
    char *lineNumBuff = malloc(10);

    // display first line if row is 0
    if (!row) mvwaddch(win, 0, 0, '1');
    for (size_t i = 0; i < buff->len; ++i) {
        // stop printing redundant lines if they're not displayed
        if (lines - row == (size_t)LINES) break;

        // line break
        if (str_at(buff, i) == '\n') {
            ++lines;
            cols = 0;
            ++lineCount;

            // display line number
            if (lines >= row && lines - row < (size_t)LINES) {
                snprintf(lineNumBuff, 10, "%lu", lineCount + 1);
                mvwaddstr(win, lines - row, 0, lineNumBuff);
            }
            continue;

            // line wrap
        } else if (cols == (size_t)COLS - maxLineNumLen - 3) {
            ++lines;
            cols = 0;
        }
        ++cols;
        if (lines >= row)
            mvwaddch(win, lines - row, cols + maxLineNumLen, str_at(buff, i));
    }
    free(lineNumBuff);
    if (*y < row)
        *y = row;
    else if (*y - row >= (size_t)LINES)
        *y = LINES + row - 1;
    if (*x <= maxLineNumLen) *x = maxLineNumLen + 1;
    wmove(win, *y - row, *x);
}
