#include "cpp.h"
#include <type_traits>
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
            bool _ab = std::is_base_of<A, B>::value;
            EXPECT_EQ(is_derived_ab, _ab);


            bool is_derived_ca = IsDerivedClass<C, A>();
            bool _ca = std::is_base_of<A, C>::value;
            EXPECT_EQ(is_derived_ca, _ca);
        }
    }
}