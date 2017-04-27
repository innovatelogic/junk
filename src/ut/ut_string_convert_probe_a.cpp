#include "str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace string_convert_probe_a
    {
        TEST(String, Str_To_Int_probe_a)
        {
            EXPECT_EQ(459, str_to_int<void>(std::string("459")));
            EXPECT_EQ(-459, str_to_int<void>(std::string("-459")));

            EXPECT_EQ(459, ConvertStringToInt<void>("459"));
            EXPECT_EQ(-459, ConvertStringToInt<void>("-459"));
        }

        TEST(String, Int_To_Str_probe_a)
        {
            EXPECT_EQ(std::string("123"), int_to_str<void>(123, 10));
            EXPECT_EQ(std::string("-123"), int_to_str<void>(-123, 10));
        }
    }
}