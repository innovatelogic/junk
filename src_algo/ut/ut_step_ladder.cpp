#include "../algo.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace step_ladder
    {
        TEST(Dp, StapLadderReq)
        {
            int count = countSteppingVariantsReq<void>(10);

            EXPECT_EQ(count, 274);
        }

        TEST(Dp, StapLadderReq_VarSteps)
        {
            int count = countSteppingVariantsReq<void>(10, 4);

            EXPECT_EQ(count, 401);
        }
    }
}