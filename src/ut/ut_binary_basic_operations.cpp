#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace binary_op
    {
        TEST(BinaryOperation, GetBit32A)
        {
            EXPECT_TRUE(GetBit32(1, 1));
            EXPECT_TRUE(GetBit32(2, 2));
            EXPECT_TRUE(GetBit32(4, 3));
            EXPECT_TRUE(GetBit32(8, 4));
            EXPECT_TRUE(GetBit32(16, 5));

            EXPECT_FALSE(GetBit32(1, 1 + 1));
            EXPECT_FALSE(GetBit32(2, 2 + 1));
            EXPECT_FALSE(GetBit32(4, 3 + 1));
            EXPECT_FALSE(GetBit32(8, 4 + 1));
            EXPECT_FALSE(GetBit32(16, 5 + 1));
        }


        TEST(BinaryOperation, SetBit32A)
        {
            EXPECT_EQ(SetBit32(0, 1), 1);
            EXPECT_EQ(SetBit32(1, 1), 1);

            EXPECT_EQ(SetBit32(2, 3), 6);
        }
    }
}