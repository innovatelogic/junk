#include "../stacks.h"
#include <gtest/gtest.h>
#include <stack>

namespace junk
{
    namespace stack_sort
    {
        int compare(const void * a, const void * b)
        {
            return (*(int*)a - *(int*)b);
        }

        TEST(Stack, StackSort)
        {
            std::stack<int> stack;

            const int N = 6;
            int val_arr[N] = { 40, 10, 100, 90, 20, 25 };

            for (int i = 0; i < N; ++i)
            {
                stack.push(val_arr[i]);
            }

            stack_sort<std::stack<int>>(stack);

            qsort(val_arr, N, sizeof(int), compare);

            for (int i = 0; i < N; ++i)
            {
                int top = stack.top();
                stack.pop();
                EXPECT_EQ(val_arr[i], top);
            }
            EXPECT_TRUE(stack.empty());
        }
    }
}