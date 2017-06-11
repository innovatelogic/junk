#include "../lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_reverse_from_nth
    {
        TEST(List, ReverseFromNth_probe_a)
        {
            {
                list<int>  lst;
                lst.push_back(1);
                lst.push_back(2);
                lst.push_back(3);
                lst.push_back(4);
                lst.push_back(5);
                lst.push_back(6);
                lst.push_back(7);

                lst.reverse_from(4);

                EXPECT_EQ(lst.head()->data, 1);
                EXPECT_EQ(lst.head()->next->data, 2);
                EXPECT_EQ(lst.head()->next->next->data, 3);
                EXPECT_EQ(lst.head()->next->next->next->data, 7);
                EXPECT_EQ(lst.head()->next->next->next->next->data, 6);
                EXPECT_EQ(lst.head()->next->next->next->next->next->data, 5);
                EXPECT_EQ(lst.head()->next->next->next->next->next->next->data, 4);
                EXPECT_EQ(lst.head()->next->next->next->next->next->next->next, nullptr);
            }

            {
                list<int>  lst;
                lst.push_back(1);
                lst.push_back(2);
                lst.push_back(3);
                lst.push_back(4);
                lst.push_back(5);
                lst.push_back(6);
                lst.push_back(7);

                lst.reverse_from(1);

                EXPECT_EQ(lst.head()->data, 7);
                EXPECT_EQ(lst.head()->next->data, 6);
                EXPECT_EQ(lst.head()->next->next->data, 5);
                EXPECT_EQ(lst.head()->next->next->next->data, 4);
                EXPECT_EQ(lst.head()->next->next->next->next->data, 3);
                EXPECT_EQ(lst.head()->next->next->next->next->next->data, 2);
                EXPECT_EQ(lst.head()->next->next->next->next->next->next->data, 1);
                EXPECT_EQ(lst.head()->next->next->next->next->next->next->next, nullptr);
            }

        }
    }
}