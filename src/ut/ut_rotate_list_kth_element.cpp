#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace rotate_list_kth_element
    {
        TEST(Lists, RotateListKthElement)
        {
            List<int> list;
            list.Insert(1);
            list.Insert(2);
            list.Insert(3);
            list.Insert(4);
            list.Insert(5);

            list.RotateOn(7);

            EXPECT_TRUE(list.head()->value == 3 && 
                list.head()->next->value == 4 &&
                list.head()->next->next->value == 5 && 
                list.head()->next->next->next->value == 1 &&
                list.head()->next->next->next->next->value == 2 &&
                list.head()->next->next->next->next->next == nullptr);
        }
    }
}