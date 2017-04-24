#include "cpp.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace is_derived_probe_a
    {
        class A {
        };

        class B : public A {
        };

        class C {
        };

        TEST(Cpp, IsDerivedClass_probe_a)
        {
            bool is_derived_ab = IsDerivedClass<B, A>();
            EXPECT_TRUE(is_derived_ab);

            bool is_derived_ca = IsDerivedClass<C, A>();
            EXPECT_FALSE(is_derived_ca);
        }
    }
}