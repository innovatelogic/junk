#include "../lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_to_int
    {
        TEST(List, IntToIntReverse)
        {
            ListExt list, list2;

            list.PushBack(7);
            list.PushBack(1);
            list.PushBack(6);
           
            list2.PushBack(5);
            list2.PushBack(9);
            list2.PushBack(2);

            int a = list.GetIntRev();
            int b = list2.GetIntRev();
            
            EXPECT_EQ(a, 617);
            EXPECT_EQ(b, 295);

            int res = list + list2;
            EXPECT_EQ(res, 912);
        }

        TEST(List, IntToInt)
        {
            ListExt list, list2;

            list.PushBack(7);
            list.PushBack(1);
            list.PushBack(6);

            list2.PushBack(5);
            list2.PushBack(9);
            list2.PushBack(2);

            int a = list.GetInt();
            int b = list2.GetInt();

            EXPECT_EQ(a, 716);
            EXPECT_EQ(b, 592);
        }

        TEST(List, OperatorPlusRevOrder)
        {
            ListExt list, list2;

            list.PushBack(7);
            list.PushBack(1);
            list.PushBack(6);

            list2.PushBack(5);
            list2.PushBack(9);
            list2.PushBack(2);

            int res = list.operator+(list2);
            EXPECT_EQ(res, 912);
        }

        TEST(List, OperatorPlusRevOrderDiffSize)
        {
            ListExt list, list2;

            list.PushBack(7);
            list.PushBack(1);
            list.PushBack(6);
            list.PushBack(1);

            list2.PushBack(5);
            list2.PushBack(9);
            list2.PushBack(2);

            int res = list.operator+(list2);
            EXPECT_EQ(res, 1912);
        }

        TEST(List, OperatorPlusForwardOrder)
        {
            ListExt list, list2;

            list.PushBack(6);
            list.PushBack(1);
            list.PushBack(7);

            list2.PushBack(2);
            list2.PushBack(9);
            list2.PushBack(5);

            int res = list.operator^(list2);
            EXPECT_EQ(res, 912);
        }

        TEST(List, OperatorPlusForwardOrderDiffSize)
        {
            ListExt list, list2;

            list.PushBack(6);
            list.PushBack(1);
            list.PushBack(7);
            list.PushBack(9);
            list.PushBack(5);

            list2.PushBack(2);
            list2.PushBack(9);
            list2.PushBack(5);

            int res = list.operator^(list2);
            EXPECT_EQ(res, 62090);
        }
    }
}