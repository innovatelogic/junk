#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace btree_all_path_sum_probe_a
    {
        typedef btree_all_path_sum_probe_a::Node TNode;

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

        //----------------------------------------------------------------------------------------------
        TEST(BTree, All_Path_Sum_probe_a)
        {
            BinaryTree tree1(AllocTree1());
            
            std::vector<std::vector<Node*>> out = tree1.path_sum(6);
        
        }
    }
}