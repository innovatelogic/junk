#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_probe_e
    {
        TEST(BST, IsBalanced_Probe_e)
        {
            //          10
            //      5      12
            //   1   6    11   13
            //     2            

            {
                BSTree tree;
                int array[] = { 10, 5, 12, 1, 2, 11, 13, 6 };
                for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                    tree.insert(array[i]);
                }
                EXPECT_TRUE(tree.is_balanced());
            }


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
                EXPECT_TRUE(tree.is_balanced());
            }

            //          10
            //       5        12
            //     1    6   11  13
            //      2             15
            //       3
            //         4
            {
                BSTree tree;
                int array[] = { 10, 5, 12, 1, 2, 11, 13, 15, 3, 4 };
                for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                    tree.insert(array[i]);
                }
                EXPECT_FALSE(tree.is_balanced());
            }
        }

        TEST(BST, Build_From_Sorted_array_IsBalanced_Probe_e)
        {
            std::vector<int> array = { 10, 5, 12, 1, 2, 11, 13, 15, 3, 4 };

            BSTree tree(array);

            EXPECT_TRUE(tree.is_balanced());
        }
    }
}