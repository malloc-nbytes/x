#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#include "utils.hpp"

void *s_malloc(size_t b) {
    void *p = malloc(b);
    if (!p) {
        fprintf(stderr, "could not alloc %zu bytes, %s\n",
                b, strerror(errno));
        exit(1);
    }
    return p;
}
