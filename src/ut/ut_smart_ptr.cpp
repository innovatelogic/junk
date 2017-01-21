#if 0
#include <iostream>
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "../smart_ptr.h"
#include <memory.h>

using ::testing::AtLeast;
using ::testing::Return;


namespace junk
{
    struct IStab
    {
        IStab()
        {}

        virtual ~IStab()
        {}

        //MOCK_METHOD0(ss, void());
    };

    class Stab : public IStab
    {
    public:
       // MOCK_METHOD0(ss, void());
    };

    TEST(SmartPtr, InitRelease)
    {
        //IStab *pp = new Stab();

        //EXPECT_CALL(*reinterpret_cast<editors::MockCommandBuffer*>(editor.GetCommandBuffer()), Undo()).Times(AtLeast(1));

        //EXPECT_CALL(*pp, ss()).Times(AtLeast(1));

        //SmartPtr<IStab> pointer(pp);
    }
}



#endif