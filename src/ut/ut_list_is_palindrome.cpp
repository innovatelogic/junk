#include "lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_is_palindrome
    {
        TEST(List, NotPalindrome_Empty)
        {
            ListExt<char> list;
            EXPECT_FALSE(list.IsPalindrome());
        }

        TEST(List, NotPalindrome_EvenSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');

            EXPECT_FALSE(list.IsPalindrome());
        }

        TEST(List, NotPalindrome_OddSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');
            list.PushBack('E');

            EXPECT_FALSE(list.IsPalindrome());
        }

        TEST(List, IsPalindrome_OneElementSize)
        {
            ListExt<char> list;

            list.PushBack('A');

            EXPECT_TRUE(list.IsPalindrome());
        }

        TEST(List, Palindrome_EvenSize)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('B');
            list.PushBack('A');

            EXPECT_TRUE(list.IsPalindrome());
        }

        TEST(List, Palindrome_OddSize)
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