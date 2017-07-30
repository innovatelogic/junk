
#include "../str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace combinations
    {
        bool in(const std::vector<std::string> &c, const std::string &str)
        {
            return std::find(c.begin(), c.end(), str) != c.end();
        }

        TEST(Combinations, StringCombinations)
        {
            Combinations comb("wxyz");

            const std::vector<std::string> &c = comb.combinations();

            // w
            // wx
            // wxy
            // wxyz
            // wxz
            // wy
            // wyz
            // wz
            // x
            // xy
            // xyz
            // xz
            // y
            // yz
            // z

            EXPECT_EQ(c.size(), 15);

            EXPECT_TRUE(in(c, "w"));
            EXPECT_TRUE(in(c, "wx"));
            EXPECT_TRUE(in(c, "wxy"));
            EXPECT_TRUE(in(c, "wxyz"));
            EXPECT_TRUE(in(c, "wxz"));
            EXPECT_TRUE(in(c, "wy"));
            EXPECT_TRUE(in(c, "wyz"));
            EXPECT_TRUE(in(c, "wz"));
            EXPECT_TRUE(in(c, "x"));
            EXPECT_TRUE(in(c, "xy"));
            EXPECT_TRUE(in(c, "xyz"));
            EXPECT_TRUE(in(c, "xz"));
            EXPECT_TRUE(in(c, "y"));
            EXPECT_TRUE(in(c, "yz"));
            EXPECT_TRUE(in(c, "z"));
        }
    }
}