#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_build_level_order_list_probe_f
    {
        TEST(BST, Build_Level_Order_List_probe_f)
        {
            //          10
            //       5      12
            //   1    6   11    13
            //     2             15

            {
                BSTree tree;
                int array[] = { 10, 5, 12, 1, 2, 11, 13, 15, 6 };
                for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                    tree.insert(array[i]);
                }

                std::vector<std::list<int>> out;
                tree.buildLevelOrder(out);

                EXPECT_EQ(out[0], std::list<int>({ 10 }));
                EXPECT_EQ(out[1], std::list<int>({ 5, 12 }));
                EXPECT_EQ(out[2], std::list<int>({ 1, 6, 11, 13 }));
                EXPECT_EQ(out[3], std::list<int>({ 2, 15 }));
            }
        }
    }
}