#include "lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_merge_sort_probe_a
    {
        TEST(List, MergeSortLists_probe_a)
        {
            List lst;
            lst.Insert(nullptr, 4);
            lst.Insert(lst.head(), 3);
            lst.Insert(lst.head()->next, 2);
            lst.Insert(lst.head()->next->next, 1);
            lst.Insert(lst.head()->next->next->next, 0);

            lst.MergeSort();

            EXPECT_EQ(lst.head()->data, 0);
            EXPECT_EQ(lst.head()->next->data, 1);
            EXPECT_EQ(lst.head()->next->next->data, 2);
            EXPECT_EQ(lst.head()->next->next->next->data, 3);
            EXPECT_EQ(lst.head()->next->next->next->next->data, 4);
        }
    }
}