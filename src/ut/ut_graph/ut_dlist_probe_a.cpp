#include "graph.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace dlist_probe_a
    {
        TEST(List, DList_insert_pobe_a)
        {
            // size <= 2 case
            {
                list obj_list;

                obj_list.insert(nullptr, 'A');

                EXPECT_EQ(obj_list.head()->data, 'A');
                EXPECT_TRUE(obj_list.head() == obj_list.tail());

                obj_list.insert(nullptr, 'B'); // insert B to front  { B, A }

                EXPECT_EQ(obj_list.head()->data, 'B');
                EXPECT_EQ(obj_list.tail()->data, 'A');
                EXPECT_EQ(obj_list.head()->next, obj_list.tail());
                EXPECT_EQ(obj_list.tail()->prev, obj_list.head());
            }

            {
                list obj_list;

                obj_list.insert(nullptr, 'A');

                EXPECT_EQ(obj_list.head()->data, 'A');
                EXPECT_TRUE(obj_list.head() == obj_list.tail());

                obj_list.insert(obj_list.head(), 'B'); // insert B to front  { A, B }

                EXPECT_EQ(obj_list.head()->data, 'A');
                EXPECT_EQ(obj_list.tail()->data, 'B');
                EXPECT_EQ(obj_list.head()->next, obj_list.tail());
                EXPECT_EQ(obj_list.tail()->prev, obj_list.head());
            }

            // size > 2 case
            {
                list obj_list;

                obj_list.insert(nullptr, 'A');
                obj_list.insert(obj_list.head(), 'B'); // {A, B}
                obj_list.insert(nullptr, 'C'); // {C, A, B}

                // check data
                EXPECT_EQ(obj_list.head()->data, 'C');
                EXPECT_EQ(obj_list.head()->next->data, 'A');
                EXPECT_EQ(obj_list.head()->next->next->data, 'B');

                // check connectivity
                EXPECT_EQ(obj_list.head()->prev, nullptr);
                EXPECT_EQ(obj_list.head()->next->prev, obj_list.head());
                EXPECT_EQ(obj_list.head()->next->next, obj_list.tail());
                EXPECT_EQ(obj_list.tail()->prev, obj_list.head()->next);
                EXPECT_EQ(obj_list.tail()->next, nullptr);
            }

            // size > 2 case
            {
                list obj_list;

                obj_list.insert(nullptr, 'A');
                obj_list.insert(obj_list.head(), 'B'); // {A, B}
                obj_list.insert(obj_list.head(), 'C'); // {A, C, B}

                // check data
                EXPECT_EQ(obj_list.head()->data, 'A');
                EXPECT_EQ(obj_list.head()->next->data, 'C');
                EXPECT_EQ(obj_list.head()->next->next->data, 'B');

                // check connectivity
                EXPECT_EQ(obj_list.head()->prev, nullptr);
                EXPECT_EQ(obj_list.head()->next->prev, obj_list.head());
                EXPECT_EQ(obj_list.head()->next->next, obj_list.tail());
                EXPECT_EQ(obj_list.tail()->prev, obj_list.head()->next);
                EXPECT_EQ(obj_list.tail()->next, nullptr);
            }

            {
                list obj_list;

                obj_list.insert(nullptr, 'A');
                obj_list.insert(obj_list.head(), 'B'); // {A, B}
                obj_list.insert(obj_list.tail(), 'C'); // {A, B, C}

                // check data
                EXPECT_EQ(obj_list.head()->data, 'A');
                EXPECT_EQ(obj_list.head()->next->data, 'B');
                EXPECT_EQ(obj_list.head()->next->next->data, 'C');

                // check connectivity
                EXPECT_EQ(obj_list.head()->prev, nullptr);
                EXPECT_EQ(obj_list.head()->next->prev, obj_list.head());
                EXPECT_EQ(obj_list.head()->next->next, obj_list.tail());
                EXPECT_EQ(obj_list.tail()->prev, obj_list.head()->next);
                EXPECT_EQ(obj_list.tail()->next, nullptr);
            }
        }
    }
}