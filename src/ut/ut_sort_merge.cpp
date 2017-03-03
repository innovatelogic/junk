
#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace sort_merge
    {
        TEST(Sorting, MergeSort)
        {
            const int size = 7;
            int array[size] = { 9, 7, 4, 0, 3, 2, 1 };
            int buffer[size];

            MergeSort<void>(array, buffer, size);

            EXPECT_EQ(array[0], 0);
            EXPECT_EQ(array[1], 1);
            EXPECT_EQ(array[2], 2);
            EXPECT_EQ(array[3], 3);
            EXPECT_EQ(array[4], 4);
            EXPECT_EQ(array[5], 7);
            EXPECT_EQ(array[6], 9);
        }

        TEST(Sorting, MergeSort_OddSize)
        {
            const int size = 8;
            int array[size] = { 9, 7, 4, 0, 3, 2, 1, 10};
            int buffer[size];

            MergeSort<void>(array, buffer, size);

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

