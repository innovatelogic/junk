#include "../dp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace dp_fib_probe_a
    {
        TEST(Dp, Fib_non_dp_probe_a)
        {
            EXPECT_EQ(fib<int>(0), 0);
            EXPECT_EQ(fib<int>(1), 1);
            EXPECT_EQ(fib<int>(2), 1);
            EXPECT_EQ(fib<int>(3), 2);
            EXPECT_EQ(fib<int>(4), 3);
            EXPECT_EQ(fib<int>(5), 5);
            EXPECT_EQ(fib<int>(6), 8);
            EXPECT_EQ(fib<int>(7), 13);
            EXPECT_EQ(fib<int>(8), 21);
            EXPECT_EQ(fib<int>(9), 34);
            EXPECT_EQ(fib<int>(10), 55);
        }

        TEST(Dp, Fib_dp_probe_a)
        {
            std::map<int, int> mem;
            EXPECT_EQ(fib_dp<int>(0, mem), 0);
            EXPECT_EQ(fib_dp<int>(1, mem), 1);
            EXPECT_EQ(fib_dp<int>(2, mem), 1);
            EXPECT_EQ(fib_dp<int>(3, mem), 2);
            EXPECT_EQ(fib_dp<int>(4, mem), 3);
            EXPECT_EQ(fib_dp<int>(5, mem), 5);
            EXPECT_EQ(fib_dp<int>(6, mem), 8);
            EXPECT_EQ(fib_dp<int>(10, mem), 55);
        }
    }
}