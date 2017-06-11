
#include "../sort_lib.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace merge_sort_probe_b
    {
        TEST(Sorting, MergeSort_probe_b)
        {
            const int size = 7;
            int array[size] = { 9, 7, 4, 0, 3, 2, 1 };
            int buffer[size];

            merge_sort<int>(array, buffer, size);

            EXPECT_EQ(array[0], 0);
            EXPECT_EQ(array[1], 1);
            EXPECT_EQ(array[2], 2);
            EXPECT_EQ(array[3], 3);
            EXPECT_EQ(array[4], 4);
            EXPECT_EQ(array[5], 7);
            EXPECT_EQ(array[6], 9);
        }

        TEST(Sorting, MergeSort_OddSize_probe_b)
        {
            const int size = 8;
            int array[size] = { 9, 7, 4, 0, 3, 2, 1, 10 };
            int buffer[size];

            merge_sort<void>(array, buffer, size);

            EXPECT_EQ(array[0], 0);
            EXPECT_EQ(array[1], 1);
            EXPECT_EQ(array[2], 2);
            EXPECT_EQ(array[3], 3);
            EXPECT_EQ(array[4], 4);
            EXPECT_EQ(array[5], 7);
            EXPECT_EQ(array[6], 9);
            EXPECT_EQ(array[7], 10);
        }
    }
}

