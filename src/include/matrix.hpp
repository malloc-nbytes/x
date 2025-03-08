#ifndef MATRIX_HPP
#define MATRIX_HPP

#include "templates/array.hpp"

struct Matrix {
    Array<Array<char>> m_data;
    Array<int> m_cols;
    size_t m_rows;
    char *m_filepath;

    // Expects alloc'd string for filepath,
    // and alloc'd string for contents. Takes
    // ownership of both.
    Matrix(const char *filepath, char *contents);

    ~Matrix(void);

    void dbg_dump(void) const;

private:
    void assert_inbounds_row(size_t i) const;
};

#endif // MATRIX_HPP
