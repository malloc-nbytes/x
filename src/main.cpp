#include <stdlib.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdint.h>

#include "matrix.hpp"
#include "io.hpp"
#include "control.hpp"
#include "utils.hpp"

#define DEF_WIN_WIDTH 80
#define DEF_WIN_HEIGHT 24

int g_win_width = DEF_WIN_WIDTH;
int g_win_height = DEF_WIN_HEIGHT;
struct termios g_old_termios;

void init_term(void) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        g_win_width = w.ws_col-1;
        g_win_height = w.ws_row-1;
    }
    else {
        perror("ioctl failed");
        fprintf(stderr,
                "[Warning]: Could not get size of terminal. Undefined behavior may occur.");
    }

    tcgetattr(STDIN_FILENO, &g_old_termios);
    struct termios raw = g_old_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_iflag &= ~IXON;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void cleanup(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &g_old_termios);
}

void help(void) {
    printf("Usage: x <file>\n");
    exit(0);
}

void display_text(Matrix *matrix, size_t start, size_t end) {
    for (size_t i = start; i < start+end; ++i) {
    }
}

int main(int argc, char **argv) {
    const char *filepath = NULL;
    char *src = NULL;

    if (argc >= 2) {
        --argc, ++argv;
        filepath = *argv;
    }

    atexit(cleanup);
    init_term();


    if (filepath) {
        src = file_to_cstr(filepath);
    }

    Matrix m = matrix_create(src, filepath);

    while (1) {
        char c;
        User_Input_Type ty = get_user_input(&c);

        switch (ty) {
        case USER_INPUT_TYPE_CTRL: assert(0 && "unimplemented"); break;
        case USER_INPUT_TYPE_ALT: assert(0 && "unimplemented"); break;
        case USER_INPUT_TYPE_ARROW: assert(0 && "unimplemented"); break;
        case USER_INPUT_TYPE_SHIFT_ARROW: assert(0 && "unimplemented"); break;
        case USER_INPUT_TYPE_NORMAL: assert(0 && "unimplemented"); break;
        case USER_INPUT_TYPE_UNKNOWN: assert(0 && "unimplemented"); break;
        default: {
            err("unknown input type");
        } break;
        }
    }

    matrix_free(&m);

    return 0;
}
