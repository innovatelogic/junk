#include "../stacks.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace two_stack_queue
    {
        TEST(Stack, TwoStackQueue)
        {
            MyQueue<int> queue;

            queue.push(1);
            queue.push(2);
            queue.push(3);

            // 3 - in
            // 2
            // 1 - out

            EXPECT_EQ(queue.top(), 1);
            queue.pop();

            EXPECT_EQ(queue.top(), 2);
            queue.pop();

            EXPECT_EQ(queue.top(), 3);
            queue.pop();
        }
    }
}