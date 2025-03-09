#ifndef MATRIX_HPP
#define MATRIX_HPP

typedef struct {
    typedef struct {
        char *data;
        size_t len, cap;
    } Line;

    struct {
        Line *data;
        size_t len, cap;
    } lines;

    char *filepath;

    size_t      col_at(size_t i, size_t j) const;
    char       &at(size_t i, size_t j);
    const char &at(size_t i, size_t j) const;
    Line       &operator[](size_t i);
    const Line &operator[](size_t i) const;
    void        assert_inbounds(size_t i, size_t j) const;
} Matrix;

Matrix matrix_create(char *src, const char *filepath);
void matrix_dbg_dump(Matrix *m);
void matrix_free(Matrix *m);

#endif // MATRIX_HPP
