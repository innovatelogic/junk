#include "arr.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace reverse_int_probe_a
    {
        TEST(Array, ReverseInt_probe_a)
        {
            EXPECT_EQ(reverse(1), 1);
            EXPECT_EQ(reverse(123), 321);
            EXPECT_EQ(reverse(100), 1);
            EXPECT_EQ(reverse(456), 654);
        }
    }
}