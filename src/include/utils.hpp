#ifndef UTILS_HPP
#define UTILS_HPP

#include <stddef.h>

#define err(msg)                                \
    do {                                        \
        fprintf(stderr, "[Error]: " msg "\n");  \
        exit(1);                                \
    } while (0)

#define err_wargs(msg, ...)                                     \
    do {                                                        \
        fprintf(stderr, "[Error]: " msg "\n", __VA_ARGS__);     \
        exit(1);                                                \
    } while (0)

#define da_append(arr, len, cap, value)                                 \
    do {                                                                \
        if ((len) >= (cap)) {                                           \
            (cap) = !(cap) ? 2 : (cap) * 2;                             \
            (arr) = (typeof((arr)[0]) *)realloc((arr), (cap) * sizeof(*(arr))); \
        }                                                               \
        (arr)[(len)] = (value);                                         \
        (len) += 1;                                                     \
    } while (0)

void *s_malloc(size_t b);

#endif // UTILS_HPP
