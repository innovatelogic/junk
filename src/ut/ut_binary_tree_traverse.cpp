#include "../junk.h"
#include <gtest/gtest.h>
#include <stack>
#include <vector>

namespace junk
{
    namespace binary_tree
    {
        typedef binary_tree::Node<int> TNode;

        //             0
        //           4   6
        //          2 1
        //             5
        TNode* AllocSampleTree()
        {
            TNode *root = new TNode(0,
                new TNode(4,
                    new TNode(2),
                    new TNode(1,
                        nullptr,
                        new TNode(5))
                    ),
                new TNode(6)
                );

            return root;
        }

        void DeallocNode(TNode *node)
        {
            if (node == nullptr) return;

            DeallocNode(node->left);
            DeallocNode(node->right);

            delete node;
        }

        //----------------------------------------------------------------------------------------------
        TEST(BinaryTree, NonRecursionTraverseDFS)
        {
            TNode *root = AllocSampleTree();
                
            std::vector<int> result;

            std::stack<TNode*> stack;

            stack.push(root);

            while (!stack.empty())
            {
                TNode *top = stack.top();

                stack.pop();

                result.push_back(top->value);

                if (top->right)
                    stack.push(top->right);

                if (top->left)
                    stack.push(top->left);
            }
            
            //             0
            //           4   6
            //          2 1
            //             5

            EXPECT_EQ(result.size(), 6);
            EXPECT_EQ(result[0], 0);
            EXPECT_EQ(result[1], 4);
            EXPECT_EQ(result[2], 2);
            EXPECT_EQ(result[3], 1);
            EXPECT_EQ(result[4], 5);
            EXPECT_EQ(result[5], 6);

            DeallocNode(root);
        }

        //----------------------------------------------------------------------------------------------
        TEST(BinarySearchTree, DFS_Traverse)
        {
            BinarySearchTree<int> *bst = new BinarySearchTree<int>();

            std::vector<int> vals = { 4, 6, 2, 1, 5, 5, 0, 3 };
            //
            //               4
            //           2         6
            //         1   3    5
            //       0            5

            for (int i : vals)
            {
                bst->Push(i);
            }

            // traverse
            std::vector<int> result = bst->GetValuesTraverseDFS();
            
            EXPECT_EQ(vals.size(), result.size());
            std::vector<int> comp = { 4, 2, 1, 0, 3, 6, 5, 5 };
            EXPECT_EQ(result, comp);

            delete bst;
        }

        TEST(BinarySearchTree, BFS_Traverse)
        {
            BinarySearchTree<int> *bst = new BinarySearchTree<int>();

            std::vector<int> vals = { 4, 6, 2, 1, 5, 5, 0, 3 };
            //
            //               4
            //           2         6
            //         1   3    5
            //       0            5

            for (int i : vals)
            {
                bst->Push(i);
            }

            // traverse
            std::vector<int> result = bst->GetValuesTraverseBFS();

            EXPECT_EQ(vals.size(), result.size());
            std::vector<int> comp = { 4, 2, 6, 1, 3, 5, 0, 5 };
            EXPECT_EQ(result, comp);
        }
    }
}