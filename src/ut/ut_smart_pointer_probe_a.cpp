
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../junk.h"
#include <memory.h>

using ::testing::AtLeast;
using ::testing::Return;

namespace junk
{
    namespace smart_ptr_probe_a
    {
        TEST(SmartPtr, AssigmentOperatorTest_probe_a)
        {
            int *p0 = new int(0);
            int *p1 = new int(1);

            smart_ptr<int> ptr0(p0);
            smart_ptr<int> ptr1(p1);

            ptr0 = ptr1;

            EXPECT_EQ(*ptr0.get(), 1);
            EXPECT_EQ(*ptr1.get(), 1);
        }
    }
}