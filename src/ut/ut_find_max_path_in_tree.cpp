#include "../junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace dfs_tree
    {
        TEST(DfsTree, FindMax)
        {
        //         A
        //      B C D E
        //      F G H I
        //      J K L M 


            ValueNode A(std::string("A"), 0);

            ValueNode B(std::string("B"), 1);
            ValueNode C(std::string("C"), 2);
            ValueNode D(std::string("D"), 3);
            ValueNode E(std::string("E"), 4);

            *(A.childs) = { &B, &C, &D, &E };

            ValueNode F(std::string("F"), 10);
            ValueNode G(std::string("G"), 20);
            ValueNode H(std::string("H"), 30);
            ValueNode I(std::string("I"), 40);

            // B C D E
            // F G H I

            *(B.childs) = { &F, &G, &I };
            *(C.childs) = { &F, &G, &H };
            *(D.childs) = { &G, &H, &I };
            *(E.childs) = { &H, &I, &F };

            // J K L M 
            ValueNode J(std::string("J"), 100);
            ValueNode K(std::string("K"), 200);
            ValueNode L(std::string("L"), 300);
            ValueNode M(std::string("M"), 400);

            // F G H I
            // J K L M 

            *(F.childs) = { &M, &J, &K };
            *(G.childs) = { &J, &K, &L };
            *(H.childs) = { &K, &L, &M };
            *(I.childs) = { &L, &M, &J };

            TreeDFS<ValueNode> tree(&A);

            size_t max = tree.FindMaxPath();

            EXPECT_EQ(max, 444);

        }

    }
}