#include "../algo.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace queue_probe_b
    {
        TEST(Queue, Queue_probe_b)
        {
            Queue<int> queue;

            queue.push(1);
            queue.push(2);
            queue.push(3);

            // 3 - in
            // 2
            // 1 - out

            EXPECT_EQ(queue.front()->value, 1);
            queue.pop();

            EXPECT_EQ(queue.front()->value, 2);
            queue.pop();

            EXPECT_EQ(queue.front()->value, 3);
            queue.pop();
        }
    }
}