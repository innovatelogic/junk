#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_find_duplicates
    {
        TEST(Lists, ListFindAndRemoveDuplicates)
        {
            List<char> list;

            list.PushBack('A');
            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('A');
            list.PushBack('C');
            list.PushBack('A');
            list.PushBack('D');
            list.PushBack('A');
            list.PushBack('A');

            list.ClearDuplicates();

            EXPECT_EQ(list.head()->value, 'A');
            EXPECT_EQ(list.head()->next->value, 'B');
            EXPECT_EQ(list.head()->next->next->value, 'C');
            EXPECT_EQ(list.head()->next->next->next->value, 'D');
            EXPECT_EQ(list.head()->next->next->next->next, nullptr);
        }
    }
}