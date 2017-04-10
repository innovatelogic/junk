#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace qsort_probe_c
    {
        TEST(Sorting, QSort_probe_c)
        {
            int a[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
            qsort_c<int>(a, 0, sizeof(a) / sizeof(int));
            for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
                EXPECT_TRUE(a[i] == i);
            }
        }
    }

    namespace qsort_probe_d
    {
        TEST(Sorting, QSort_probe_d)
        {
            int a[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
            qsort<int>(a, 0, sizeof(a) / sizeof(int));
            for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
                EXPECT_TRUE(a[i] == i);
            }
        }
    }
}