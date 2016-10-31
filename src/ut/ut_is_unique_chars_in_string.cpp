#include "../is_unique_chars_in_string.h"
#include "gtest/gtest.h"

namespace junk
{
    namespace string
    {
        TEST(String, is_unique_chars_in_string)
        {
            std::string comp("abcdefgh");
            EXPECT_TRUE(is_unique_chars_in_string(comp));

            std::string comp2("abcdeagh");
            EXPECT_FALSE(is_unique_chars_in_string(comp2));
        }


        TEST(String, is_unique_low_letters_in_string)
        {
            std::string comp("abcdefgh");
            EXPECT_TRUE(is_unique_low_letters_in_string(comp));

            std::string comp2("abcdeagh");
            EXPECT_FALSE(is_unique_low_letters_in_string(comp2));
        }
    }
}