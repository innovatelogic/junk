#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace binary_op
    {
        TEST(BinaryOperation, GetBit32)
        {
            EXPECT_TRUE(GetBit32(1, 0));
            EXPECT_TRUE(GetBit32(2, 1));
            EXPECT_TRUE(GetBit32(4, 2));
            EXPECT_TRUE(GetBit32(8, 3));
            EXPECT_TRUE(GetBit32(16, 4));

            EXPECT_FALSE(GetBit32(1, 0 + 1));
            EXPECT_FALSE(GetBit32(2, 1 + 1));
            EXPECT_FALSE(GetBit32(4, 2 + 1));
            EXPECT_FALSE(GetBit32(8, 3 + 1));
            EXPECT_FALSE(GetBit32(16, 4 + 1));
        }

        TEST(BinaryOperation, SetBit32)
        {
            EXPECT_EQ(SetBit32(0, 0), 1);
            EXPECT_EQ(SetBit32(1, 0), 1);

            EXPECT_EQ(SetBit32(2, 2), 6);

            EXPECT_EQ(SetBit32(32, 3), 40);
        }

        TEST(BinaryOperation, ClearBit32)
        {
            EXPECT_EQ(ClearBit32(40, 3), 32);
            EXPECT_EQ(ClearBit32(168, 5), 136);
        }

        TEST(BinaryOperation, ClearUpToBit32)
        {
            EXPECT_EQ(ClearUpToBit32(136, 6), 128);
            EXPECT_EQ(ClearUpToBit32(15, 2), 8);
        }
    }
}