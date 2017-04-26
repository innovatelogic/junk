#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace matrix_cw
    {
        TEST(Array, MatrixCW)
        {
            int matrix[] = { 
                2,	3,	4,	13,	17,
                8,	5,	7,	14,	18,
                9,	12,	1,	15,	19,
                0,	6,	10,	16,	20,
                23, 24, 25, 26, 27,
            };
            std::vector<int> out;
            MatrixCW<int>(matrix, 5, 5, out);
        }
    }
}