#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace qsort_probe_a
    {
        TEST(Sorting, QSort_probe_a)
        {
            int a[] = { 7, 6, 5, 4, 3, 2, 1, 0};
            myqsort<int>(a, 0, sizeof(a) / sizeof(int));

        }
    }
}