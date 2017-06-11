#include "../sort_lib.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace sort_selection_rec
    {
        TEST(Sorting, SelectionSortRecursive)
        {
            std::vector<int> v{ 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
            std::vector<int> r{ 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            SelectionSortRec(v);

            EXPECT_EQ(v, r);
        }
    }
}