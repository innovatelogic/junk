#include "../str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace string_subsequences_probe_a
    {
        TEST(String, Subsequences_sum_probe_a)
        {
            StrSubsequences test(std::string("1234"));
            EXPECT_EQ(test.Sum(), 1979);
        }
    }
}