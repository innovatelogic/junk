#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace reverse_int_probe_a
    {
        TEST(Array, ReverseInt_probe_a)
        {
            EXPECT_EQ(reverse<void>(1), 1);
            EXPECT_EQ(reverse<void>(123), 321);
            EXPECT_EQ(reverse<void>(100), 1);
            EXPECT_EQ(reverse<void>(456), 654);
        }
    }
}