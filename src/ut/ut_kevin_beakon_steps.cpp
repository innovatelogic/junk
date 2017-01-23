#include "../junk.h"
#include "gtest/gtest.h"

namespace junk
{
    namespace kevin_beakon
    {
        TEST(KevinBeakon, ShortestPath)
        {
            Graph<char> graph;

            graph.AddNode('A', { 'B', 'F' });
            graph.AddNode('B', { 'A', 'C' });
            graph.AddNode('C', { 'B', 'D' });
            graph.AddNode('D', { 'C', 'E' });
            graph.AddNode('E', { 'D', 'F' });
            graph.AddNode('F', { 'E', 'A' });

            int count = 0;
            
            bool res = graph.FindShortest('A', 'D', count);
            
            EXPECT_TRUE(res);
        }
    }
}