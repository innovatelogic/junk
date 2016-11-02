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
    }
}