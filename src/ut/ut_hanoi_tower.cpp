#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace hanoi_tower
    {
        TEST(HanoiTower, Arrange)
        {
            const int n = 3;
            Tower towers[3] = {1, 2, 3};

            for (int i = n - 1; i >= 0; i--){
                towers[0].add(i);
            }

            MoveDiscs(n, towers[0], towers[2], towers[1]);

            EXPECT_EQ(towers[2].top(), 0);
            towers[2].pop();

            EXPECT_EQ(towers[2].top(), 1);
            towers[2].pop();

            EXPECT_EQ(towers[2].top(), 2);
            towers[2].pop();
        }
    }
}