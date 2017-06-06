#include "../bst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_tree_probe_c
    {

        TEST(BST, Probe_c_Balance)
        {
            //          10
            //      5      12
            //   1    6
            //     2            
            //
            //        |
            //
            //        5
            //    1      10
            //      2   6   12
            {
                BSTree tree;
                int array[] = { 10, 5, 12, 1, 2, 6 };
                for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                    tree.push(array[i]);
                }
                EXPECT_FALSE(tree.is_balanced());

                tree.rotate_right();

                EXPECT_TRUE(tree.is_balanced());
            }
        }
    }
}