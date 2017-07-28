
#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace array_combinations_probe_a
    {
        bool in(const std::vector<std::string> &c, const std::string &str)
        {
            return std::find(c.begin(), c.end(), str) != c.end();
        }

        TEST(Array, StringCombinations_probe_a)
        {
            std::vector<std::string> out;
            
            combinations<void>(std::string("wxyz"), out);

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

            EXPECT_EQ(out.size(), 15);

            EXPECT_TRUE(in(out, "w"));
            EXPECT_TRUE(in(out, "wx"));
            EXPECT_TRUE(in(out, "wxy"));
            EXPECT_TRUE(in(out, "wxyz"));
            EXPECT_TRUE(in(out, "wxz"));
            EXPECT_TRUE(in(out, "wy"));
            EXPECT_TRUE(in(out, "wyz"));
            EXPECT_TRUE(in(out, "wz"));
            EXPECT_TRUE(in(out, "x"));
            EXPECT_TRUE(in(out, "xy"));
            EXPECT_TRUE(in(out, "xyz"));
            EXPECT_TRUE(in(out, "xz"));
            EXPECT_TRUE(in(out, "y"));
            EXPECT_TRUE(in(out, "yz"));
            EXPECT_TRUE(in(out, "z"));
        }
    }
}