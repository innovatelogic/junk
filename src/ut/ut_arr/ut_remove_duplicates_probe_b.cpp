#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace remove_duplicates_probe_b
    {
        TEST(Array, RemoveDuplicatesProbe_b)
        {
            int array[] = {10,1,2,1,1,3,5,2,6,3,7,8,9,10 };
            int new_size = RemoveDuplicates<int>(array, sizeof (array)/sizeof(int));

            EXPECT_EQ(new_size, 9);
            EXPECT_TRUE(
                array[0] == 1 &&
                array[1] == 2 &&
                array[2] == 3 &&
                array[3] == 5 &&
                array[4] == 6 &&
                array[5] == 7 &&
                array[6] == 8 &&
                array[7] == 9 &&
                array[8] == 10);
        }
    }
}