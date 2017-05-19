#pragma once

#include "mathlib.h"

namespace junk
{
    namespace cie_conv
    {
            struct Canvas
            {
                pixel **pixels;
                const size_t rows;
                const size_t cols;

                Canvas(size_t rows, size_t cols)
                    : rows(rows)
                    , cols(cols)
                    , pixels(nullptr)
                {}

                void allocate();
                void free();
            };
    }
}