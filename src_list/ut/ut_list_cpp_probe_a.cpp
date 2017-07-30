#include "../lst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace list_cpp_probe_a
    {
        TEST(List, List_cpp_HeadTail_probe_a)
        {
            List list;

            int array[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };

            for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                list.insert(nullptr, array[i]);
            }

            EXPECT_EQ(list.head()->value, 9);
            EXPECT_EQ(list.tail()->value, 0);
        }
    }
}