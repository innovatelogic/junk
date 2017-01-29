#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_to_int
    {
        TEST(Lists, IntToIntReverse)
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
        }

        TEST(Lists, IntToInt)
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
    }
}