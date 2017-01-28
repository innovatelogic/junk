#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_find_duplicates
    {
        TEST(Lists, ListFindAndRemoveDuplicates)
        {
            ListExt<char> list;

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

    namespace list_find_nth_from_end
    {
        TEST(Lists, ListFindNthFromEnd_EmptyList)
        {
            ListExt<char> list;
            EXPECT_EQ(list.FindNthFromEnd(0), nullptr);
        }

        TEST(Lists, ListFindNthFromEnd)
        {
            ListExt<char> list;

            list.PushBack('A');
            list.PushBack('B');
            list.PushBack('C');
            list.PushBack('D');
            list.PushBack('E');
            list.PushBack('F');

            lists::ListNode<char> *node0 = list.FindNthFromEnd(0);
            lists::ListNode<char> *node1 = list.FindNthFromEnd(1);
            lists::ListNode<char> *node2 = list.FindNthFromEnd(2);
            lists::ListNode<char> *node3 = list.FindNthFromEnd(3);
            lists::ListNode<char> *node4 = list.FindNthFromEnd(4);
            lists::ListNode<char> *node5 = list.FindNthFromEnd(5);
            lists::ListNode<char> *node6 = list.FindNthFromEnd(6);

            EXPECT_EQ(node0->value, 'F');
            EXPECT_EQ(node1->value, 'E');
            EXPECT_EQ(node2->value, 'D');
            EXPECT_EQ(node3->value, 'C');
            EXPECT_EQ(node4->value, 'B');
            EXPECT_EQ(node5->value, 'A');
            EXPECT_EQ(node6, nullptr);
        }
    }

    namespace list_rearrange_by_kth_element
    {
        TEST(Lists, ListRearrangeByElem)
        {
            ListExt<int> list;

            list.PushBack(7);
            list.PushBack(2);
            list.PushBack(1);
            list.PushBack(4);
            list.PushBack(3);
            list.PushBack(6);
            list.PushBack(5);

            auto *median = list.head()->next->next->next;
            EXPECT_EQ(median->value, 4);
            list.RearrangeByElement(median);

            std::vector<int> vcheck_min = { 1, 2, 3 };
            auto *it = list.head();
            while (it != median)
            {
                std::vector<int>::iterator find = std::find(vcheck_min.begin(), vcheck_min.end(), it->value);

                EXPECT_TRUE(find != vcheck_min.end());

                vcheck_min.erase(find);

                it = it->next;
            }

            std::vector<int> vcheck_max = { 4, 5, 6, 7 };
            it = median;
            while (it)
            {
                std::vector<int>::iterator find = std::find(vcheck_max.begin(), vcheck_max.end(), it->value);

                EXPECT_TRUE(find != vcheck_max.end());

                vcheck_max.erase(find);

                it = it->next;
            }
        }
    }
}