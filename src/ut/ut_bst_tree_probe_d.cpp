#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_tree_probe_d
    {

        TEST(BST, NodeDistance_Probe_d)
        {
            //          10
            //       5      12
            //   1       11    13
            //     2             15

            BSTree tree;
            int array[] = { 10, 5, 12, 1, 2, 11, 13, 15 };
            for (int i = 0; i < sizeof(array) / sizeof(int); ++i){
                tree.push(array[i]);
            }

            EXPECT_EQ(tree.distance(1, 15), 5);
            EXPECT_EQ(tree.distance(15, 1), 5);

            EXPECT_EQ(tree.distance(2, 11), 5);
            EXPECT_EQ(tree.distance(11, 2), 5);

            EXPECT_EQ(tree.distance(5, 2), 2);
            EXPECT_EQ(tree.distance(5, 5), 0);
            EXPECT_EQ(tree.distance(12, 11), 1);

            EXPECT_EQ(tree.distance(0, 11), -1);
        }

        TEST(BST, RemoveNode_Probe_d)
        {
            BSTree tree;
            int array[] = { 10, 5, 12, 1, 2, 11, 13, 15 };
            for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                tree.push(array[i]);
            }

            //          10
            //       5      12
            //   1       11    13
            //     2             15

            int array2[] = { 5, 10,  12, 1, 2, 15, 11, 13 };
            for (int i = 0; i < sizeof(array2) / sizeof(int); ++i) {
                EXPECT_TRUE(tree.remove(array2[i]));
            }
        }
    }
}