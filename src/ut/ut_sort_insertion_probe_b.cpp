#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace isertion_sort_probe_b
    {
        TEST(Sorting, InsertionSort_probe_b)
        {
            std::vector<int> v{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
            std::vector<int> r{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            insertion_sort<int>(v);

            EXPECT_EQ(v, r);
        }
    }
}