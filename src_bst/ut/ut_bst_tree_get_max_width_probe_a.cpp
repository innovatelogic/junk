#include "../bst.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace bst_max_width
    {
        TEST(BST, BST_Max_Width_probe_a)
        {
            BSTree tree;
            tree.insert(100);
            tree.insert(50);
            tree.insert(175);
            tree.insert(15);
            tree.insert(65);
            tree.insert(165);
            tree.insert(185);

            EXPECT_EQ(tree.max_width(), 4);
        }

        TEST(BST, BST_Max_Width_skew_probe_a)
        {
            BSTree tree;
            tree.insert(100);
            tree.insert(175);
            tree.insert(185);

            EXPECT_EQ(tree.max_width(), 1);
        }
    }
}