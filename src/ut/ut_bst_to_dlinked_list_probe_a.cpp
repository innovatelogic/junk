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

    namespace binary_tree_to_dlinked_list_probe_b
    {
        struct node
        {
            int data;
            node* left;
            node* right;
        };

        /* This is the core function to convert Tree to list. This function follows
        steps 1 and 2 of the above algorithm */
        node* bintree2listUtil(node* root)
        {
            // Base case
            if (root == NULL)
                return root;

            // Convert the left subtree and link to root
            if (root->left != NULL)
            {
                // Convert the left subtree
                node* left = bintree2listUtil(root->left);

                // Find inorder predecessor. After this loop, left
                // will point to the inorder predecessor
                for (; left->right != NULL; left = left->right);

                // Make root as next of the predecessor
                left->right = root;

                // Make predecssor as previous of root
                root->left = left;
            }

            // Convert the right subtree and link to root
            if (root->right != NULL)
            {
                // Convert the right subtree
                node* right = bintree2listUtil(root->right);

                // Find inorder successor. After this loop, right
                // will point to the inorder successor
                for (; right->left != NULL; right = right->left);

                // Make root as previous of successor
                right->left = root;

                // Make successor as next of root
                root->right = right;
            }

            return root;
        }

        // The main function that first calls bintree2listUtil(), then follows step 3 
        //  of the above algorithm
        node* bintree2list(node *root)
        {
            // Base case
            if (root == NULL)
                return root;

            // Convert to DLL using bintree2listUtil()
            root = bintree2listUtil(root);

            // bintree2listUtil() returns root node of the converted
            // DLL.  We need pointer to the leftmost node which is
            // head of the constructed DLL, so move to the leftmost node
            while (root->left != NULL)
                root = root->left;

            return (root);
        }

        /* Helper function that allocates a new node with the
        given data and NULL left and right pointers. */
        node* newNode(int data)
        {
            node* new_node = new node;
            new_node->data = data;
            new_node->left = new_node->right = NULL;
            return (new_node);
        }


        TEST(BST, TestTest)
        {
            // Let us create the tree shown in above diagram
            node *root = newNode(10);
            root->left = newNode(12);
            root->right = newNode(15);
            root->left->left = newNode(25);
            root->left->right = newNode(30);
            root->right->left = newNode(36);

            // Convert to DLL
            node *head = bintree2list(root);
        }
    }
}
