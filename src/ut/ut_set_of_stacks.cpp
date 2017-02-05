#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace set_of_stacks
    {
        TEST(SetOfStacks, PushPop)
        {
            SetOfStacks<int> stack_set;

            stack_set.Push(0);
            stack_set.Push(1);
            stack_set.Push(2);

            EXPECT_EQ(stack_set.Size(), 1);

            stack_set.Push(3);
            stack_set.Push(4);
            stack_set.Push(5);

            EXPECT_EQ(stack_set.Size(), 2);

            stack_set.Pop();
            stack_set.Pop();
            stack_set.Pop();

            EXPECT_EQ(stack_set.Size(), 1);

            stack_set.Pop();
            stack_set.Pop();
            stack_set.Pop();

            EXPECT_EQ(stack_set.Size(), 0);
        }
        
        TEST(SetOfStacks, PopAt)
        {
            SetOfStacks<int> stack_set;

            stack_set.Push(0);
            stack_set.Push(1);
            stack_set.Push(2);

            EXPECT_EQ(stack_set.Size(), 1);

            stack_set.Push(3);
            stack_set.Push(4);
            stack_set.Push(5);

            EXPECT_EQ(stack_set.Size(), 2);

            stack_set.Push(6);
            stack_set.Push(7);
            stack_set.Push(8);

            EXPECT_EQ(stack_set.Size(), 3);

            stack_set.PopAt(1);
            stack_set.PopAt(1);
            stack_set.PopAt(1);

            EXPECT_EQ(stack_set.Size(), 2);
        }
    }
}