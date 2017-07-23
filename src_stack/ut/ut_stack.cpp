#include "../stacks.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace stack
    {
        TEST(Stack, StackBase)
        {
            Stack<char> _stack;

            EXPECT_EQ(_stack.Top(), nullptr);

            _stack.Push('A');
            EXPECT_EQ(_stack.Top()->value, 'A');

            _stack.Push('B');
            EXPECT_EQ(_stack.Top()->value, 'B');

            _stack.Push('C');
            EXPECT_EQ(_stack.Top()->value, 'C');

            _stack.Pop();
            EXPECT_EQ(_stack.Top()->value, 'B');

            _stack.Pop();
            EXPECT_EQ(_stack.Top()->value, 'A');

            _stack.Pop();
            EXPECT_EQ(_stack.Top(), nullptr);
        }
    }
}