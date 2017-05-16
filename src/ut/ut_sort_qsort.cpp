#include "junk.h"
#include <gtest/gtest.h>

#include <iostream>
#include <memory>
#include <vector>

namespace junk
{
    namespace sort_qsort
    {
        TEST(Sorting, QSort)
        {
            {
                std::vector<int> v{ 8, 7, 6, 5, 4, 3, 2, 1, 0 };
                std::vector<int> r{ 0, 1, 2, 3, 4, 5, 6, 7, 8 };

                QSort(v);

                EXPECT_EQ(v, r);
            }

            //10,1,2,1,1,3,5,2,6,3,7,8,9,10

            {
                std::vector<int> v{ 10,1,2,1,1,3,5,2,6,3,7,8,9,10 };
                std::vector<int> r{ 1,1,1,2,2,3,3,5,6,7,8,9,10,10 };

                QSort(v);

                EXPECT_EQ(v, r);
            }
        }
    }
}