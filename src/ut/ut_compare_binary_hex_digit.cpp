#include "../junk.h"
#include "gtest/gtest.h"

namespace junk
{

    TEST(Numbers, StrHEX_vs_Bin)
    {
        int i = numbers::str_to_int("100", 2);

        EXPECT_TRUE(numbers::compare_hex_bin("3F3", "001111110011"));
    }
}