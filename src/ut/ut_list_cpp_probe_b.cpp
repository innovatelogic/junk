#include "lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_cpp_probe_b
    {
        TEST(List, List_cpp_DeepCopy_probe_a)
        {
            List list;

            int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                list.insert(nullptr, array[i]);
            }

            EXPECT_EQ(list.head()->value, 9);
            EXPECT_EQ(list.tail()->value, 0);

            List list_copy;
            list_copy.deep_copy(list);

            EXPECT_EQ(list.head()->value, 9);
            EXPECT_EQ(list.tail()->value, 0);

            EXPECT_EQ(list_copy.head()->value, 9);
            EXPECT_EQ(list_copy.tail()->value, 0);
        }
    }
}