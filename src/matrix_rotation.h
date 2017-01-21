#pragma once

#include "defexport.h"

namespace junk
{
    namespace matrix
    {
        template<class T>
        JUNK_EXPORT void matrix_rotate_cw(T **arr, size_t size)
        {
            for (size_t i = 0; i < size / 2; ++i)
            {
                for (size_t j = i; j < size - (i + 1); ++j)
                {
                    int d = j - i;
                    int n_th = size - 1;

                    T buff = arr[i][j];

                    std::swap(buff, arr[i + d][n_th - i]);
                    std::swap(buff, arr[n_th - i][n_th - i - d]);
                    std::swap(buff, arr[n_th - i - d][i]);
                    std::swap(buff, arr[i][j]);
                }
            }
        }
    }
}