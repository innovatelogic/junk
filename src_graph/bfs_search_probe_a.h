#pragma once

#include <queue>
#include <unordered_map>

namespace junk
{
	namespace graph_bfs_probe_a
	{
		struct Node
		{
			Node(int data) : data(data){}
			int data;
			std::vector<Node*> links;
		};
		
		template<typename T>
		bool search_path(Node *start, Node *end, std::vector<Node*> &path)
		{
			if (!start || !end){
				return false;
			}
			
			std::queue<Node*> wave;
			wave.push(start);
			
			std::unordered_map<Node*, Node*> visited;
			visited.insert({start, nullptr});
			
			while (!wave.empty())
			{
				Node *top = wave.front();
				
				if (top == end)
				{
					Node *iter = top;
					while (iter)
					{
                        std::unordered_map<Node*, Node*>::iterator prev = visited.find(iter);
						path.push_back(prev->first);
						iter = prev->second;
					}
					return true;
				}
				
				wave.pop();
				
				for (size_t i = 0; i < top->links.size(); i++)
				{
					if (visited.find(top->links[i]) == visited.end())
					{
						wave.push(top->links[i]);
						visited.insert({top->links[i], top});
					}
				}
			}
            return false;
		}
	}
}