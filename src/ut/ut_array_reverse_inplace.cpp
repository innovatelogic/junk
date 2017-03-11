#include "junk.h"
#include <gtest/gtest.h>
#include <vector>

namespace array
{
    namespace array_reverse_inplace
    {
        TEST(Array, Reverse_Even)
        {
            std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8 };
            Reverse<int>(arr);

            std::vector<int> check = { 8, 7, 6, 5, 4, 3, 2, 1 };
            EXPECT_EQ(arr, check);
        }

        TEST(Array, Reverse_Odd)
        {
            std::vector<int> arr = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };
            Reverse<int>(arr);

            std::vector<int> check = { 9, 8, 7, 6, 5, 4, 3, 2, 1 };
            EXPECT_EQ(arr, check);
        }
    }
}