#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace btree_is_subtree
    {
        typedef btree_is_subtree::Node TNode;

        //             0
        //           4   6
        //          2  1
        //            3 5
        TNode* AllocTree1()
        {
            return new TNode(0,
                new TNode(4,
                    new TNode(2),
                    new TNode(1,
                        new TNode(3),
                        new TNode(5))
                ),
                new TNode(6)
            );
        }


        //             0
        //           4   6
        //          2  1
        //            3 7
        TNode* AllocTree2()
        {
            return new TNode(0,
                new TNode(4,
                    new TNode(2),
                    new TNode(1,
                        new TNode(3),
                        new TNode(7))
                ),
                new TNode(6)
            );
        }

        //  1
        // 3 5
        TNode* AllocTree3()
        {
            return new TNode(1, new TNode(3), new TNode(5));
        }

        //----------------------------------------------------------------------------------------------
        TEST(BTree, IsSubtree_probe_a)
        {
            BinaryTree tree1(AllocTree1());
            BinaryTree tree1_(AllocTree1());
            BinaryTree tree2(AllocTree2());
            BinaryTree tree3(AllocTree3());

            EXPECT_TRUE(tree1.is_subequal(tree1_));
            EXPECT_FALSE(tree1.is_subequal(tree2));
            EXPECT_TRUE(tree1.is_subequal(tree3));
        }
    }
}