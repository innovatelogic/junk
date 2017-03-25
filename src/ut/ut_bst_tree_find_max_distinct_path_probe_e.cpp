#include "junk.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_find_max_distinct_path_probe_e
    {
        TEST(BST, FindMaxDistinctPath_probe_e)
        {
            BSTree tree;

            //                  100
            //           50             175
            //      30       60      165      185    
            //        30           164   165     185
            //
            //

            tree.Insert(100);
            tree.Insert(50);
            tree.Insert(175);
            tree.Insert(30);
            tree.Insert(60);
            tree.Insert(165);
            tree.Insert(185);
            tree.Insert(30);
            tree.Insert(60);
            tree.Insert(164);
            tree.Insert(165);
            tree.Insert(185);

            std::vector<int> path = { 100, 175, 165, 164 };
            EXPECT_EQ(tree.FindLonghestDistinctPath(), path);
        }
    }
}