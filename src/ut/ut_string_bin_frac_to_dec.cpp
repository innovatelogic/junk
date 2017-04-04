#include "str.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace string_bin_frac_to_dec
    {
        TEST(String, Bin_Frac_To_Dec_probe_a)
        {
            EXPECT_EQ(6.625, str_bin_frac_to_dec<void>(std::string("110.101")));
            EXPECT_EQ(5.8125, str_bin_frac_to_dec<void>(std::string("101.1101")));
        }
    }
}