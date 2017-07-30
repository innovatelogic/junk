#include "../trees.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace tree_is_balanced
    {
        TEST(Trees, IsBalanced_StatusFalse)
        {
            Node *root = new Node();
            root->left = new Node();
            root->left->left = new Node();
            root->left->left->left = new Node();
            root->right = new Node();

            BTree<Node> tree(root);
            EXPECT_FALSE(tree.isBalanced());

            delete root->right;
            delete root->left->left->left;
            delete root->left->left;
            delete root->left;
            delete root;
        }

        TEST(Trees, IsBalanced_StatusTrue)
        {
            Node *root = new Node();
            root->left = new Node();
            root->left->left = new Node();
            root->left->right = new Node();
            root->left->left->left = new Node();
            root->right = new Node();
            root->right->left = new Node();

            BTree<Node> tree(root);
            EXPECT_TRUE(tree.isBalanced());

            delete root->right->left;
            delete root->right;
            delete root->left->left->left;
            delete root->left->left;
            delete root->left->right;
            delete root->left;
            delete root;
        }
    }
}