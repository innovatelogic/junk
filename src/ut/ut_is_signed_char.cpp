#include <gtest/gtest.h>

namespace junk
{
    namespace is_signed_char
    {
        /*
        §3.9.1¶1
            Plain char, signed char, and unsigned char are three distinct types
        */

        TEST(Cpp, IsSignedChar)
        {
            if (std::is_signed<char>::value) {
                auto a = std::is_same<char, signed char>::value;
                EXPECT_FALSE(a);
            }
            else {
                 auto a = std::is_same<char, unsigned char>::value;
                 EXPECT_TRUE(false);
            }
        }
    }
}