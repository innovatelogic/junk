#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace stack_probe_a
    {
        TEST(Stack, StackBase_probe_a)
        {
            Stack<char> s;

            EXPECT_EQ(s.top(), nullptr);

            s.push('A');
            EXPECT_EQ(s.top()->value, 'A');

            s.push('B');
            EXPECT_EQ(s.top()->value, 'B');

            s.push('C');
            EXPECT_EQ(s.top()->value, 'C');

            s.pop();
            EXPECT_EQ(s.top()->value, 'B');

            s.pop();
            EXPECT_EQ(s.top()->value, 'A');

            s.pop();
            EXPECT_EQ(s.top(), nullptr);
        }
    }
}