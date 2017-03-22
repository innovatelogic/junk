#include "junk.h"
#include <time.h>
#include <vector>
#include <map>
#include <stdlib.h>
#include <time.h>
#include <gtest/gtest.h>

namespace junk
{
    namespace array_frequency_rand
    {
        TEST(Array, ArrayFrequencyRand)
        {
            srand((unsigned)time(0));

            std::vector<std::pair<int, unsigned int>> arr = {
                {0, 0},
                {1, 2},
                {3, 3},
                {5, 0},
                {10, 10}
            };

            std::map<int, int> res = { {0, 0}, {1, 0}, {3, 0}, {5, 0}, {10, 0} };

            freq_random_selector<int> selector(arr);

            for (int i = 0; i < 100; i++)
            {
                int out;
                EXPECT_TRUE(selector.get_rand(out));
                res[out]++;
            }

            EXPECT_EQ(res[0], 0);
            EXPECT_EQ(res[5], 0);
            EXPECT_TRUE(res[1] < res[3] && res[3] < res[10]);
        }
    }
}