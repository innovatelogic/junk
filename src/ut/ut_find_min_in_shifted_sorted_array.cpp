#include "../junk.h"
#include <gtest/gtest.h>
#include <algorithm>

namespace junk
{
    //----------------------------------------------------------------------------------------------
    TEST(Array, SortedArray_FindMinIfShifted)
    {
        const int MIN = 0;
        std::vector<int> arr = {MIN, 1, 2, 3 , 4 }; // , 4, 5, 6, 7, 8, 9, 10, 11

        for (size_t i = 0; i < arr.size(); ++i)
        {
            int min = find_min_in_shifted_sorted_array(&arr[0], 0, arr.size() - 1);

            EXPECT_EQ(min, MIN);

            std::rotate(arr.begin(), arr.begin() + 1, arr.end());
        }  
    }
}