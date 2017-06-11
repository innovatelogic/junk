
#include "../sort_lib.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace sort_selection_stable
    {
        TEST(Sorting, SelectionStable)
        {
            std::vector<std::pair<int, int>> v{ {0, 1}, {2, 0}, {0, 3}, {1, 0}, {0, 2} };
            std::vector<std::pair<int, int>> r{ { 0, 1 },{ 0, 3 },{ 0, 2 },{ 1, 0 }, { 2, 0 }};

            SortSelectionStable(v);

            EXPECT_EQ(v, r);
        }
    }
}