
#include "../arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace two_sum_problem
    {
        TEST(Array, TwoSumInArray_SumEqual)
        {
            std::vector<int> a{ 33, 12, 54, 65, 11, 99, 2, 1, 0 };

            int k, n;
            bool res = TwoSumProblem<void>(a, 100, k, n);

            EXPECT_TRUE(res);
            EXPECT_EQ(k, 1);
            EXPECT_EQ(n, 99);
        }

        TEST(Array, TwoSumInArray_SumEqual_Hash)
        {
            std::vector<int> a{ 33, 12, 54, 65, 11, 99, 2, 1, 0 };

            int k, n;
            bool res = TwoSumProblemHash<void>(a, 100, k, n);

            EXPECT_TRUE(res);
            EXPECT_EQ(k + n, 100);
        }

        TEST(Array, TwoSumInArray_SumEqualFalse)
        {
            std::vector<int> a{ 33, 12, 54, 65, 11, 99, 2, 1, 0 };

            int k, n;
            bool res = TwoSumProblem<void>(a, 1000, k, n);
            EXPECT_FALSE(res);
        }

        TEST(Array, TwoSumInArray_SumEqualFalse_Hash)
        {
            std::vector<int> a{ 33, 12, 54, 65, 11, 99, 2, 1, 0 };

            int k, n;
            bool res = TwoSumProblemHash<void>(a, 1000, k, n);
            EXPECT_FALSE(res);
        }
    }
}