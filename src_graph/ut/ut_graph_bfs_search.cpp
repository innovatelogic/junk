#include "../graph.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace graph_bfs_probe_a
    {
        TEST(Graph, BFS_probe_a)
        {

            //            n3
            //         n1     n4
            //     n0            n6 n7
            //         n2     n5

            Node *n0 = new Node(0);
            Node *n1 = new Node(1);
            Node *n2 = new Node(2);
            Node *n3 = new Node(3);
            Node *n4 = new Node(4);
            Node *n5 = new Node(5);
            Node *n6 = new Node(6);
            Node *n7 = new Node(7);

            n0->links = { n1, n2 };
            n1->links = { n3, n0 };
            n2->links = { n5, n0 };
            n3->links = { n4, n1, n0 };
            n4->links = { n6, n3 };
            n5->links = { n6, n2 };
            n6->links = { n7, n4, n5 };

            std::vector<Node*> out;
            bool flag = search_path<void>(n0, n7, out);

            EXPECT_TRUE(flag);

            EXPECT_TRUE(out[0] == n7 && out[1] == n6 && out[2] == n5 && out[3] == n2 && out[4] == n0);
            
            delete n0, n1, n2, n3, n4, n5, n6, n7;
        }
    }
}