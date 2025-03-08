#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <stdio.h>
#include <stddef.h>

#include "utils.hpp"

template <typename T>
struct Array {
    T *m_data;
    size_t m_len, m_cap;

    Array(void) : m_data(new T[1]), m_len(0), m_cap(1) {}

    Array(T *data, size_t len) : m_data(new T[1]), m_len(0), m_cap(1) {
        for (size_t i = 0; i < len; ++i) {
            add(data[i]);
        }
    }

    ~Array(void) {
        delete[] m_data;
    }

    Array(const Array<T> &other) : m_data(new T[other.m_cap]), m_len(other.m_len), m_cap(other.m_cap) {
        if (m_cap > 0) {
            m_data = new T[m_cap];
            memcpy(m_data, other.m_data, m_len * sizeof(T));
        }
    }

    inline void rm(size_t i) {
        assert_inbounds(i);
        if (!memmove(&m_data[i], &m_data[i+1], (m_len - i - 1) * sizeof(T))) {
            err_wargs("memmove failed, %s", strerror(errno));
        }
        --m_len;
    }

    inline void add(T d) {
        if (m_len >= m_cap) {
            resize();
        }
        m_data[m_len++] = d;
    }

    inline size_t length(void) const {
        return m_len;
    }

    inline void clear(void) {
        m_len = 0;
    }

    inline const T &operator[](size_t i) const {
        assert_inbounds(i);
        return m_data[i];
    }

    inline T &operator[](size_t i) {
        assert_inbounds(i);
        return m_data[i];
    }

private:
    inline void resize(void) {
        size_t old_cap = m_cap;
        m_cap = m_cap ? m_cap * 2 : 2;
        T *_data = new T[m_cap];
        if (old_cap != 0) {
            memcpy(_data, m_data, old_cap * sizeof(T));
            delete[] m_data;
        }
        m_data = _data;
    }

    inline void assert_inbounds(size_t i) const {
        if (!(i >= 0 && i < m_len)) {
            err_wargs("Index %zu is out of bounds of length %zu", i, m_len);
        }
    }
};

#endif // ARRAY_HPP
