#include "../sort_lib.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace qsort_probe_b
    {
        TEST(Sorting, QSort_probe_b)
        {
            int a[] = { 7, 6, 5, 4, 3, 2, 1, 0 };
            _qsort_probe_b<void>(a, 0, sizeof(a) / sizeof(int));

            for (int i = 0; i < sizeof(a) / sizeof(int); ++i) {
                EXPECT_TRUE(a[i] == i);
            }
        }
    }
}
