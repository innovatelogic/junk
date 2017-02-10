#include "junk.h"
#include <gtest/gtest.h>
#include <stack>

namespace junk
{
    namespace stack_sort
    {
        TEST(Stack, StackSort)
        {
            std::stack<int> stack;
            stack.push(1);
            stack.push(5);
            stack.push(3);
            stack.push(2);

            stack_sort<std::stack<int>>(stack);

            const int N = 4;
            int cmp_arr[N] = { 1, 2, 3, 5 };

            for (int i = 0; i < N; ++i)
            {
                int top = stack.top();
                stack.pop();
                EXPECT_EQ(cmp_arr[i], top);
            }
            EXPECT_TRUE(stack.empty());
        }
    }
}