#include "junk.h"
#include <gtest/gtest.h>


namespace junk
{
    namespace stack_min_track
    {
        TEST(Stack, StackMinTrack)
        {
            StackMin<int> stack_min;

            EXPECT_EQ(stack_min.Top(), nullptr);

            stack_min.Push(5);
            EXPECT_EQ(stack_min.Top()->value, 5);
            EXPECT_EQ(stack_min.Min()->value, 5);

            stack_min.Push(6);
            EXPECT_EQ(stack_min.Top()->value, 6);
            EXPECT_EQ(stack_min.Min()->value, 5);

            stack_min.Push(3);
            EXPECT_EQ(stack_min.Top()->value, 3);
            EXPECT_EQ(stack_min.Min()->value, 3);

            stack_min.Push(7);
            EXPECT_EQ(stack_min.Top()->value, 7);
            EXPECT_EQ(stack_min.Min()->value, 3);

            stack_min.Pop();
            EXPECT_EQ(stack_min.Top()->value, 3);
            EXPECT_EQ(stack_min.Min()->value, 3);

            stack_min.Pop();
            EXPECT_EQ(stack_min.Top()->value, 6);
            EXPECT_EQ(stack_min.Min()->value, 5);
        }
    }
}
