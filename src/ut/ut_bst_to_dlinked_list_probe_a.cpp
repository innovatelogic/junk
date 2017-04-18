#include "bst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace binary_tree_to_dlinked_list_probe_a
    {
        TEST(BST, BinTreeToDlist_probe_a)
        {
            //          10
            //      5       15
            //   4   6   12           

            BSTree tree;
            int array[] = { 10, 5, 15, 4, 6, 12 };
            for (int i = 0; i < sizeof(array) / sizeof(int); ++i) {
                tree.insert(array[i]);
            }
            Node* head = tree.to_dlist();

            EXPECT_EQ(head->data, 4);
            EXPECT_EQ(head->right->data, 5);
            EXPECT_EQ(head->right->right->data, 6);
            EXPECT_EQ(head->right->right->right->data, 10);
            EXPECT_EQ(head->right->right->right->right->data, 12);
            EXPECT_EQ(head->right->right->right->right->right->data, 15);
        }
    }
}
