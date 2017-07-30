#include "../arr.h"
#include <gtest/gtest.h>

namespace array
{
    namespace is_palindrome
    {
        TEST(Array, IsStrindPalindrome_Even)
        {
            EXPECT_TRUE(isPalindrome<std::string> ("AdfikkifdA"));
            EXPECT_FALSE(isPalindrome<std::string>("Adfik_ifdA"));
        }

        TEST(Array, IsStrindPalindrome_Odd)
        {
            EXPECT_TRUE(isPalindrome<std::string> ("1234567654321"));
            EXPECT_FALSE(isPalindrome<std::string>("1234567_54321"));
        }
    }
}