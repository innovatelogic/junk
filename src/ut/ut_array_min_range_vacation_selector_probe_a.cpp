#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace vacation_selector
    {
        TEST(Array, MinCompleteSetInArray_VacationSelector_probe_a)
        {
            {
                VacationSelector vacation(
                { {'A', 1}, {'A', 1 }, {'B', 2}, {'B', 2}, {'C', 4} }
                );

                EXPECT_EQ(vacation.min_idx(), 1);
                EXPECT_EQ(vacation.value(), 9);
                EXPECT_EQ(vacation.size(), 4);
            }

            {
                VacationSelector vacation(
                { { 'A', 3 },{ 'A', 2 },{ 'A', 1 },{ 'A', 2 },{ 'A', 4 } }
                );

                EXPECT_EQ(vacation.min_idx(), 2);
                EXPECT_EQ(vacation.value(), 1);
                EXPECT_EQ(vacation.size(), 1);
            }

            {
                VacationSelector vacation(
                { { 'A', 3 },{ 'B', 2 },{ 'C', 5 },{ 'A', 1 },{ 'B', 1 },{ 'B', 2 },{ 'C', 1 } }
                );

                EXPECT_EQ(vacation.min_idx(), 3);
                EXPECT_EQ(vacation.value(), 5);
                EXPECT_EQ(vacation.size(), 4);
            }
        }
    }
}