
#include "../lst.h"
#include <gtest/gtest.h>

//----------------------------------------------------------------------------------------------
TEST(List, Circular_probe_a)
{
    // 0 1 2 3 4 5
    //     9 8 7 6 
    ListElement<int>* array[10] = { nullptr };
    for (int i = 0; i < 10; ++i) 
    {
        array[i] = new ListElement<int>(i);
        if (i > 0) { 
            array[i - 1]->set_next(array[i]);
        }
    }
    array[9]->set_next(array[2]);

    EXPECT_TRUE(junk::IsCircularList(array[0]));

    delete [] *array;
}

//----------------------------------------------------------------------------------------------
TEST(List, NonCircular_probe_a)
{
    ListElement<int>* array[10] = { nullptr };
    for (int i = 0; i < 10; ++i)
    {
        array[i] = new ListElement<int>(i);
        if (i > 0) {
            array[i - 1]->set_next(array[i]);
        }
    }
    EXPECT_FALSE(junk::IsCircularList(array[0]));

    delete [] *array;
}
