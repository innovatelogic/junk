#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_is_circular
    {
        TEST(Lists, IsListCircular)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');
            list.PushBack('E');
            list.PushBack('F');

            list.AddEndLoop(list.head()->next->next);

            lists::ListNode<char> *node = list.IsCircular();

            EXPECT_TRUE(node != nullptr);
            EXPECT_EQ(node->value, 'C');

            list.head()->next->next->next->next->next->next = nullptr;
        }

        TEST(Lists, IsListCircularEndToHead)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');
            list.PushBack('E');
            list.PushBack('F');

            list.AddEndLoop(list.head());

            lists::ListNode<char> *node = list.IsCircular();

            EXPECT_TRUE(node != nullptr);
            EXPECT_EQ(node->value, 'A');

            list.head()->next->next->next->next->next->next = nullptr;
        }

        TEST(Lists, IsListCircularEmpty)
        {
            ListExt<char> list;

            lists::ListNode<char> *node = list.IsCircular();

            EXPECT_TRUE(node == nullptr);
        }
    }
}