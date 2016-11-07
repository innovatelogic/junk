#include "../strings.h"
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

            reverse(str);

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

                int len = strlen(str);
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
    }
}