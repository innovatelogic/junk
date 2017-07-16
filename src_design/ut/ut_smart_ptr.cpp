
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../smart_ptr.h"
#include <memory.h>

using ::testing::AtLeast;
using ::testing::Return;

namespace junk
{
    template<class T>
    struct MockCtrl
    {
        MockCtrl(T *p)
            : ptr(p)
            , counter(1) {}

        //MOCK_METHOD0(count, int());
        //MOCK_METHOD0(dec, int());
        //MOCK_METHOD0(inc, int());

        T *ptr;
        int counter;
    };


    TEST(Design, SmartPtr_AssigmentOperatorTest)
    {
        int *p0 = new int(0);
        int *p1 = new int(1);

        //MockCtrl<int> *ctrl = new MockCtrl<int>(pp);

        //EXPECT_CALL(*ctrl, dec()).Times(AtLeast(1));

        //EXPECT_CALL(*pp, ss()).Times(AtLeast(1));

        SmartPtr<int> ptr0(p0);
        SmartPtr<int> ptr1(p1);

        ptr0 = ptr1;

        EXPECT_EQ(**ptr0, 1);
        EXPECT_EQ(**ptr1, 1);
    }
}