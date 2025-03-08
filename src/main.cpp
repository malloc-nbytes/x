#include <stdlib.h>
#include <assert.h>
#include <sys/ioctl.h>
#include <stdio.h>
#include <unistd.h>
#include <termios.h>
#include <stdint.h>

#include "templates/array.hpp"
#include "matrix.hpp"
#include "io.hpp"
#include "utils.hpp"

#define DEF_WIN_WIDTH 80
#define DEF_WIN_HEIGHT 24

namespace config {
    namespace term {
        int width = DEF_WIN_WIDTH;
        int height = DEF_WIN_HEIGHT;
        struct termios old_termios;
    };

    uint32_t flags = 0x0;
};

void init_term(void) {
    struct winsize w;
    if (ioctl(STDOUT_FILENO, TIOCGWINSZ, &w) == 0) {
        config::term::width = w.ws_col-1;
        config::term::height = w.ws_row-1;
    }
    else {
        perror("ioctl failed");
        fprintf(stderr,
                "[Warning]: Could not get size of terminal. Undefined behavior may occur.");
    }

    tcgetattr(STDIN_FILENO, &config::term::old_termios);
    struct termios raw = config::term::old_termios;
    raw.c_lflag &= ~(ECHO | ICANON);
    raw.c_iflag &= ~IXON;
    tcsetattr(STDIN_FILENO, TCSANOW, &raw);
}

void cleanup(void) {
    tcsetattr(STDIN_FILENO, TCSANOW, &config::term::old_termios);
}

int main(void) {
    atexit(cleanup);
    init_term();

    const char *filepath = "/home/zdh/dev/EARL/src/main.c";
    char *contents = io::file_to_cstr(filepath);

    Matrix m(filepath, contents);
    m.dbg_dump();

    return 0;
}
