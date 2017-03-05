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
        }
    }
}