#include "graph.h"
#include <gtest/gtest.h>

namespace junk
{
    namespace dijkstra_probe_a
    {
        TEST(Graph, Dijkstra_probe_a)
        {
            const int V = 9;

            int graph[V][V] =
            { { 0, 4, 0, 0, 0, 0, 0, 8, 0 },
            { 4, 0, 8, 0, 0, 0, 0, 11, 0 },
            { 0, 8, 0, 7, 0, 4, 0, 0, 2 },
            { 0, 0, 7, 0, 9, 14, 0, 0, 0 },
            { 0, 0, 0, 9, 0, 10, 0, 0, 0 },
            { 0, 0, 4, 14, 10, 0, 2, 0, 0 },
            { 0, 0, 0, 0, 0, 2, 0, 1, 6 },
            { 8, 11, 0, 0, 0, 0, 1, 0, 7 },
            { 0, 0, 2, 0, 0, 0, 6, 7, 0 }
            };

            std::vector<int> dist = dijkstra<V>(graph, 0);

            EXPECT_EQ(dist, std::vector<int>({0, 4, 12, 19, 21, 11, 9, 8, 14}));
        }
    }
}