#include "../bst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_find_next_successor
    {
        typedef bst_find_next_successor::Node TNode;

        //                    100
        //              50           175
        //          15      65    165   185
        //           
        TNode* AllocTree1()
        {
            return new TNode(100,
                new TNode(50,
                    new TNode(15),
                    new TNode(65)
                ),
                new TNode(175,
                    new TNode(165),
                    new TNode(185)
                )
            );
        }

        //----------------------------------------------------------------------------------------------
        TEST(BST, Find_Next_Successor)
        {
            BSTree tree(AllocTree1());

            Node* next = tree.next_node(tree.root()->left->right);

            EXPECT_EQ(next->value, 100);
        }
    }
}