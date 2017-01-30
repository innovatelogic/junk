#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_is_palindrome
    {
        TEST(Lists, NotPalindrome_Empty)
        {
            ListExt<char> list;
            EXPECT_FALSE(list.IsPalindrome());
        }

        TEST(Lists, NotPalindrome_EvenSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');

            EXPECT_FALSE(list.IsPalindrome());
        }

        TEST(Lists, NotPalindrome_OddSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');
            list.PushBack('E');

            EXPECT_FALSE(list.IsPalindrome());
        }

        TEST(Lists, IsPalindrome_OneElementSize)
        {
            ListExt<char> list;

            list.PushBack('A');

            EXPECT_TRUE(list.IsPalindrome());
        }

        TEST(Lists, Palindrome_EvenSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('B');
            list.PushBack('A');

            EXPECT_TRUE(list.IsPalindrome());
        }

        TEST(Lists, Palindrome_OddSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('B');
            list.PushBack('A');

            EXPECT_TRUE(list.IsPalindrome());
        }
    }
}