#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace permutations_probe_a
    {
        TEST(Permutation, StringPermutation_probe_a)
        {
            std::string str("abcd");
            std::vector<std::string> out;

            Permutator r(str);
            r.permutate();
            out = r.out();

            EXPECT_TRUE(std::find(out.begin(), out.end(), "abcd") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "abdc") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "acbd") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "acdb") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "adbc") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "adcb") != out.end());

            EXPECT_TRUE(std::find(out.begin(), out.end(), "bacd") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "badc") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "bcad") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "bcda") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "bdac") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "bdca") != out.end());

            EXPECT_TRUE(std::find(out.begin(), out.end(), "cabd") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "cadb") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "cbad") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "cbda") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "cdab") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "cdba") != out.end());

            EXPECT_TRUE(std::find(out.begin(), out.end(), "dabc") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "dacb") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "dbac") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "dbca") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "dcab") != out.end());
            EXPECT_TRUE(std::find(out.begin(), out.end(), "dcba") != out.end());
            EXPECT_EQ(out.size(), 24);
        }
    }
}