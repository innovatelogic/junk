
#include "../str.h"
#include "gtest/gtest.h"

namespace junk
{
    namespace string
    {
        TEST(String, rotate_string)
        {
            char str[] = "0123456789";

            rotate_right(str);

            EXPECT_EQ(strcmp(str, "9012345678"), 0);
        }

        TEST(String, reverse)
        {
            char str[] = "0123456789";

            is_unique_chars_in_string::reverse(str);

            EXPECT_EQ(strcmp(str, "9876543210"), 0);
        }

        TEST(String, is_permutation)
        {
            char str1[] = "00112233445566778899";
            char str2[] = "01120334245657678989";
            char str3[] = "01120334245657678999";

            EXPECT_TRUE(is_permutation(str1, str2));
            EXPECT_FALSE(is_permutation(str2, str3));
        }

        TEST(String, replace_in_str)
        {
            {
                char *str = "This is test string";

                size_t len = strlen(str);
                char *str2 = new char[len + 1]; // +1 null terminator
                strncpy_s(str2, len + 1, str, len);

                replace_str(&str2, ' ', "%TEST%");
                EXPECT_TRUE(!strcmp(str2, "This%TEST%is%TEST%test%TEST%string"));

                delete [] str2;
            }
            
            {
                char *str = "a b c d e f";

                int len = strlen(str);
                char *str2 = new char[len + 1]; // +1 null terminator
                strncpy_s(str2, len + 1, str, len);

                replace_str(&str2, ' ', "A");
                EXPECT_TRUE(!strcmp(str2, "aAbAcAdAeAf"));

                delete str2;
            }

            {
                char *str = "abcdef";

                int len = strlen(str);
                char *str2 = new char[len + 1]; // +1 null terminator
                strncpy_s(str2, len + 1, str, len);

                replace_str(&str2, ' ', "%TEST%");
                EXPECT_TRUE(!strcmp(str2, "abcdef"));

                delete str2;
            }
        }

        TEST(String, compress_string)
        {
            std::string str0("aabcccccaaa");
            EXPECT_EQ(compress(str0), std::string("a2b1c5a3"));

            std::string str1("abcde");
            EXPECT_EQ(compress(str1), std::string("abcde"));
        }

        TEST(String, ReverseWords)
        {
            char str1[] = "This is test string";
            reverse_words(str1);
            EXPECT_EQ(std::string("string test is This"), std::string(str1));

            char str2[] = "This";
            reverse_words(str2);
            EXPECT_EQ(std::string("This"), std::string(str2));

            char str3[] = "  This  ";
            reverse_words(str3);
            EXPECT_EQ(std::string("  This  "), std::string(str3));

            char str4[] = "a";
            reverse_words(str4);
            EXPECT_EQ(std::string("a"), std::string(str4));

            char str5[] = "";
            reverse_words(str5);
            EXPECT_EQ(std::string(""), std::string(str5));
        }
    }
}
