#include "../binary_basic_operations.h"
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

        TEST(BinaryOperation, ClearFromBit32)
        {
            EXPECT_EQ(ClearFromBit32(120, 3), 8);
            EXPECT_EQ(ClearFromBit32(920, 4), 24);
        }

        TEST(BinaryOperation, UpdateBit32)
        {
            EXPECT_EQ(UpdateBit32(920, 3, 0), 912);

            std::vector<int> v1(1, 2);
            std::vector<int> v2{ 1, 2 };
            size_t a = v1.size();
            size_t b = v2.size();
        }

        TEST(BinaryOperation, MergeTwoNum32)
        {
            EXPECT_EQ(MergeTwoNum32(1024, 19, 2, 6), 1100);
            EXPECT_EQ(MergeTwoNum32(1024, 19, 2, 5), 1024);
        }


        TEST(BinaryOperation, CountOneByteInNum32)
        {
            EXPECT_EQ(CountOneByteInNum32(5), 2);
            EXPECT_EQ(CountOneByteInNum32(8), 1);
        }

        TEST(BinaryOperation, GetNextClosestSameBits)
        {
            int val = GetNextClosestSameBits(22);
            EXPECT_EQ(val, 25);
            EXPECT_EQ(CountOneByteInNum32(val), CountOneByteInNum32(25));

            val = GetNextClosestSameBits(45);
            EXPECT_EQ(val, 46);
            EXPECT_EQ(CountOneByteInNum32(val), CountOneByteInNum32(45));
        }

        TEST(BinaryOperation, GetPrevClosetSameBits)
        {
            int val = GetPrevClosetSameBits(5);
            EXPECT_EQ(val, 3);
            EXPECT_EQ(CountOneByteInNum32(val), CountOneByteInNum32(3));

            EXPECT_EQ(GetPrevClosetSameBits(2), 1);
            EXPECT_EQ(GetPrevClosetSameBits(7), -1);
            EXPECT_EQ(GetPrevClosetSameBits(1), -1);
        }

        TEST(BinaryOperation, BitSwapRequired)
        {
            EXPECT_EQ(BitSwapRequired(2, 1), 2);
            EXPECT_EQ(BitSwapRequired(5, 2), 3);
        }

        TEST(BinaryOperation, IsLittleEndian)
        {
            bool isLSB = IsLittleEndian();
            EXPECT_TRUE(isLSB); // not equal test
        }

        /*struct AAA
        {
            AAA()
            {
                int k = 0;
            }

            AAA(const AAA& obj)
            {
                int k = 0;
            }

            ~AAA()
            {
                int d = 0;
            }

            int __k;
        };

        std::vector<AAA> makeVec()
        {
            return { AAA(), AAA() };
        }

        void SetAAA(std::vector<AAA> &v)
        {
            int d = 0;
        }*/

        TEST(BinaryOperation, SwapEvenOddBits32)
        {
            //SetAAA(makeVec());

            EXPECT_EQ(SwapEvenOddBits32(165), 90);
        }

    }
}