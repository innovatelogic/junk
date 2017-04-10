#include "dp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace dp_fib_probe_a
    {
        TEST(DP, Fib_non_dp_probe_a)
        {
            EXPECT_EQ(fib(0), 0);
            EXPECT_EQ(fib(1), 1);
            EXPECT_EQ(fib(2), 1);
            EXPECT_EQ(fib(3), 2);
            EXPECT_EQ(fib(4), 3);
            EXPECT_EQ(fib(5), 5);
            EXPECT_EQ(fib(6), 8);
            EXPECT_EQ(fib(7), 13);
            EXPECT_EQ(fib(8), 21);
            EXPECT_EQ(fib(9), 34);
            EXPECT_EQ(fib(10), 55);
        }

        TEST(DP, Fib_dp_probe_a)
        {
            std::map<int, int> mem;
            EXPECT_EQ(fib_dp(0, mem), 0);
            EXPECT_EQ(fib_dp(1, mem), 1);
            EXPECT_EQ(fib_dp(2, mem), 1);
            EXPECT_EQ(fib_dp(3, mem), 2);
            EXPECT_EQ(fib_dp(4, mem), 3);
            EXPECT_EQ(fib_dp(5, mem), 5);
            EXPECT_EQ(fib_dp(6, mem), 8);
            EXPECT_EQ(fib_dp(10, mem), 55);
        }
    }
}