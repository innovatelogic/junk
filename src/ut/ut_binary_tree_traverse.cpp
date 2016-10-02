#include "../binary_tree.h"
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

        TEST(BinaryTree, NonRecursionTraverse)
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
    }
}