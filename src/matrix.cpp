#include <string.h>

#include <utility>

#include "matrix.hpp"
#include "templates/array.hpp"
#include "utils.hpp"
#include "dyn_array.h"

Matrix::Matrix(const char *filepath, char *contents) {
    m_filepath = strdup(filepath);

    dyn_array(char, buf);

    for (size_t i = 0; contents[i]; ++i) {
        char c = contents[i];
        if (c == '\n') {
            Array<char> chars(buf.data, buf.len);
            m_data.add(std::move(chars));
            memset(buf.data, '\0', buf.len);
            buf.len = 0;
        } else {
            dyn_array_append(buf, c);
        }
    }
}

void Matrix::dbg_dump() const {
    for (size_t i = 0; i < m_rows; ++i) {
        for (size_t j = 0; j < m_data[i].length(); ++j) {
            putchar(m_data[i][j]);
        }
        putchar('\n');
    }
}

Matrix::~Matrix(void) {
    free(m_filepath);
}

void Matrix::assert_inbounds_row(size_t i) const {
    assert(i >= 0 && i < m_rows);
}
