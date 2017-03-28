#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_tree_is_bst_probe_f
    {
        TEST(BST, IsTreeBST_NonValid_A)
        {
            BSTree tree;

            //  100
            //     100
            //   100

            tree.m_root = new Node(100);
            tree.m_root->right = new Node(100);
            tree.m_root->right->left = new Node(100);
            tree.m_root->right->right = new Node(100);
            EXPECT_FALSE(tree.is_bst());
        }

        TEST(BST, IsTreeBST_NonValid_B)
        {
            BSTree tree;

            //      3
            //    2   5
            //  1  4
            tree.m_root = new Node(3);
            tree.m_root->right = new Node(5);
            tree.m_root->left = new Node(2);
            tree.m_root->left->left = new Node(1);
            tree.m_root->left->right = new Node(4);
            EXPECT_FALSE(tree.is_bst());
        }

        TEST(BST, IsTreeBST_Valid_A)
        {
            BSTree tree;

            //        7
            //     3     7
            //   1  4      8   
            tree.m_root = new Node(7);
            tree.m_root->left = new Node(3);
            tree.m_root->right = new Node(7);
            tree.m_root->left->left = new Node(1);
            tree.m_root->left->right = new Node(4);
            tree.m_root->right->right = new Node(8);
            EXPECT_TRUE(tree.is_bst());
        }
    }
}