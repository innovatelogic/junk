#pragma once

#include <stdlib.h>
#include <vector>

namespace junk
{
	namespace bellman_ford_probe_a
	{
		struct Edge
		{
			int src;
			int dest;
			int weight;
		};
		
		struct Graph
		{
			int V; // num of vert
			int E; // num of edge
			bool negative_cycle;
			Edge *edge;
		};
		
        template<typename T>
		Graph* createGraph(int V, int E)
		{
			Graph* graph = (Graph*)malloc(sizeof(Graph));
			graph->V = V;
			graph->E = E;
			graph->negative_cycle = false;
			graph->edge = (Edge*)malloc(graph->E * sizeof(Edge));
			return graph;
		}
		
        template<typename T>
		void freeGraph(Graph* graph)
		{
			free(graph->edge);
			free(graph);
		}
		
        template<typename T>
        std::vector<int> BellmanFord(Graph *graph, int src)
		{
			int V = graph->V;
			int E = graph->E;
			std::vector<int> dist(V, INT_MAX);
			
			dist[src] = 0;
			
			for (int i = 1; i <= V-1; i++)
			{
				for (int j = 0; j < E; j++)
				{
					int u = graph->edge[j].src;
					int v = graph->edge[j].dest;
					int weight = graph->edge[j].weight;
					if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
						dist[v] = dist[u] + weight;
					}
				}
			}
			
            // detect cycles
			for (int i = 0; i < E; i++)
			{
				int u = graph->edge[i].src;
				int v = graph->edge[i].dest;
				int weight = graph->edge[i].weight;
				if (dist[u] != INT_MAX && dist[u] + weight < dist[v]){
					graph->negative_cycle = true;
				}
			}

            return dist;
		}
	}
}