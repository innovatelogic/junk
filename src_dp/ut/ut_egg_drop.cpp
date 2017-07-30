#include "../dp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace egg_drop
    {
        TEST(Dp, EggDrop)
        {
            int k = egg<void>(2, 100);
            EXPECT_EQ(k, 14);
        }
    }
}