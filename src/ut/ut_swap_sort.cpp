#include "../swap_sort.h"
#include <gtest/gtest.h>

namespace junk
{
    TEST(SwapSort, Sort)
    {
        std::vector<int> arr = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
        std::vector<int> sorted = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
        
        swap_sort(arr);

        EXPECT_EQ(arr, sorted);
    }
}