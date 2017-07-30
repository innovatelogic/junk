#include "../lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_c_probe_a
    {
        TEST(List, List_C_probe_a)
        {
            int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            ListNode *head = nullptr;

            for (int i = 0; i < sizeof(array) / sizeof(int); i++)
            {
                if (head == nullptr) {
                    head = new ListNode(array[i]);
                    continue;
                }

                insertFront<ListNode>(&head, new ListNode(array[i]));
            }

            EXPECT_EQ(size<ListNode>(head), 9);
            EXPECT_TRUE(tail<ListNode>(head)->value == 1);

            int count = 0;

            // delete middle element 5
            remove<ListNode>(&head, head->next->next->next->next);
            EXPECT_EQ(size<ListNode>(head), 8);

            while (head){
                remove<ListNode>(&head, count++ % 2 == 0 ? head : tail<ListNode>(head));
            }

            EXPECT_EQ(size<ListNode>(head), 0);
        }

        TEST(List, List_C_Reverse_probe_a)
        {
            int array[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            ListNode *head = nullptr;

            for (int i = 0; i < sizeof(array) / sizeof(int); i++)
            {
                if (head == nullptr) {
                    head = new ListNode(array[i]);
                    continue;
                }

                insertFront<ListNode>(&head, new ListNode(array[i]));
            }

            reverse<ListNode>(&head);

            EXPECT_TRUE(head->value == 1 &&
                head->next->value == 2 &&
                head->next->next->value == 3 &&
                head->next->next->next->value == 4 &&
                head->next->next->next->next->value == 5 &&
                head->next->next->next->next->next->value == 6 &&
                head->next->next->next->next->next->next->value == 7 &&
                head->next->next->next->next->next->next->next->value == 8 &&
                head->next->next->next->next->next->next->next->next->value == 9 &&
                head->next->next->next->next->next->next->next->next->next == nullptr);

            while (head) {
                remove<ListNode>(&head, head);
            }
            EXPECT_EQ(head, nullptr);
        }
    }

}