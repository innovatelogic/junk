#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace check_string_braces
    {
        TEST(Array, CheckBracesString)
        {
            EXPECT_FALSE(BracesCheck("{sdfs(dfsfsd)}<1><").check());
            EXPECT_TRUE(BracesCheck("{sdfs(dfsfsd)}[(1)]").check());
            EXPECT_TRUE(BracesCheck("{}()[]<>").check());
        }
    }
}