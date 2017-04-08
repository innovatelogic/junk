#pragma once

#include <limits.h>

namespace junk
{
	namespace dijkstra_probe_a
	{
        template<size_t size>
		int minDistance(std::vector<int> dist, std::vector<bool> sptSet)
		{
			int min = INT_MAX, min_index;
			for (size_t v = 0; v < size; v++)
			{
				if (sptSet[v] == false && dist[v] <= min){
					min = dist[v]; 
					min_index = v;
				}
			}
			return min_index;
		}
		
        template<size_t size>
        std::vector<int> dijkstra(int (&graph)[size][size], int src)
		{
			const size_t V = size;
			
			std::vector<int> dist(V, INT_MAX); 
			std::vector<bool> sptSet(V, false);
			
			dist[src] = 0;
			
			for (int count = 0; count < V - 1; count++)
			{
				int u = minDistance<size>(dist, sptSet);
				
				sptSet[u] = true;
				
				for (int v = 0; v < size; v++)
				{
					if (!sptSet[v] && graph[u][v] && dist[u] != INT_MAX &&
						dist[u] + graph[u][v] < dist[v])
                    {
							dist[v] = dist[u] + graph[u][v];
					}
				}
			}
            return dist;
		}
	}
}