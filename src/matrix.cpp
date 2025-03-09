#include <stdio.h>
#include <string.h>

#include "matrix.hpp"
#include "utils.hpp"
#include "dyn_array.h"

const Matrix::Line &Matrix::operator[](size_t i) const {
    return this->lines.data[i];
}

Matrix::Line &Matrix::operator[](size_t i) {
    if (i >= this->lines.len) {
        err_wargs("row %zu is out of bounds of length %zu",
                  lines.len, i);
    }
    return this->lines.data[i];
}

char &Matrix::at(size_t i, size_t j) {
    this->assert_inbounds(i, j);
    return (*this)[i].data[j];
}

const char &Matrix::at(size_t i, size_t j) const {
    this->assert_inbounds(i, j);
    return (*this)[i].data[j];
}

void Matrix::assert_inbounds(size_t i, size_t j) const {
    if (i >= this->lines.len) {
        err_wargs("row %zu is out of bounds of length %zu",
                  this->lines.len, i);
    }
    if (j >= this->lines.data[i].len) {
        err_wargs("column %zu is out of bounds of length %zu",
                  this->lines.data[i].len, j);
    }
}

Matrix::Line line_create(char *s, size_t len, size_t cap) {
    return (Matrix::Line) {
        .data = strdup(s),
        .len = len,
        .cap = cap,
    };
}

Matrix matrix_create(char *src, const char *filepath) {
    const char *filepath_actual = filepath ? filepath : "[new file]";

    Matrix m = (Matrix) {
        .lines = {
            .data = NULL,
            .len = 0,
            .cap = 0,
        },
        .filepath = strdup(filepath_actual),
    };

    if (!src || !filepath) return m;

    dyn_array(char, buf);

    for (size_t i = 0; src[i]; ++i) {
        char c = src[i];
        if (c == '\n') {
            Matrix::Line line = line_create(buf.data, buf.len, buf.cap);
            dyn_array_append(m.lines, line);
            memset(buf.data, 0, buf.len), buf.len = 0;
        } else {
            dyn_array_append(buf, c);
        }
    }

    if (buf.len > 0) {
        Matrix::Line line = line_create(buf.data, buf.len, buf.cap);
        dyn_array_append(m.lines, line);
    }

    dyn_array_free(buf);

    return m;
}

void matrix_dbg_dump(Matrix *m) {
    for (size_t i = 0; i < m->lines.len; ++i) {
        const Matrix::Line &line = (*m)[i];
        for (size_t j = 0; j < line.len; ++j) {
            putchar(line.data[j]);
        }
        putchar('\n');
    }
}

void matrix_free(Matrix *m) {
    for (size_t i = 0; i < m->lines.len; ++i) {
        free(m->lines.data[i].data);
    }
    if (m->lines.data) {
        free(m->lines.data);
    }
    free(m->filepath);
}
