#include "../graph.h"
#include "gtest/gtest.h"

namespace junk
{
    namespace kevin_beakon
    {
        TEST(Graph, KevinBeakon_ShortestPath)
        {
            Graph<char> graph;

            graph.AddNode('A', { 'B', 'K' });
            graph.AddNode('B', { 'A', 'C' });
            graph.AddNode('C', { 'B', 'D' });
            graph.AddNode('D', { 'C', 'E' });
            graph.AddNode('E', { 'D', 'F' });
            graph.AddNode('F', { 'E', 'K' });
            graph.AddNode('K', { 'A', 'F' });

            int count = 0;
            
            bool res = graph.FindShortest('A', 'D', count);
            
            EXPECT_TRUE(res);

            std::list<char> path;

            graph.Trace(char('D'), path);

            EXPECT_EQ(path, std::list<char>({ 'A', 'B', 'C', 'D' }));
        }
    }
}