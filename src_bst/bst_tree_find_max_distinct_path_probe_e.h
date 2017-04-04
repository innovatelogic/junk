#pragma once 

#include <vector>
#include <queue>

namespace junk
{
	namespace bst_find_max_distinct_path_probe_e
	{
		struct Node
		{
			Node(int val): value(val), left(nullptr), right(nullptr) {}
			int value;
			Node *left;
			Node *right;
        };

		class BSTree
		{
			public:
			    BSTree(): m_root(nullptr){}

			    ~BSTree() { Clear(); }
		
			    void Insert(int value)
			    {
				    if (!m_root)
				    {
					    m_root = new Node(value);
				    }
				    else
				    {
					    Node *iter = m_root;
					    while (iter)
					    {
						    if (value < iter->value)
						    {
							    if (!iter->left){
								    iter->left = new Node(value);
								    return;
							    }
							    iter = iter->left;
						    }
						    else{
							
							    if (!iter->right){
								    iter->right = new Node(value);
								    return;
							    }
							    iter = iter->right;
						    }
					    }
				    }
			    }
			
			    void Clear()
			    {
				    std::queue<Node*> q;
				    if (m_root){
					    q.push(m_root);
					    while(!q.empty())
					    {
						    Node *top = q.front();
						    q.pop();
						
						    if (top->left){
							    q.push(top->left);
						    }
						    if (top->right){
							    q.push(top->right);
						    }
						    delete top;
					    }
				    }
			    }
			
			    std::vector<int> FindLonghestDistinctPath()
			    {
				    if (m_root){
					    FindLonghestDistinctPath(m_root, std::vector<int>() = {});
				    }
				    return m_max_path;
			    }

			private:
				void FindLonghestDistinctPath(Node *root, std::vector<int> &path)
				{
					if (!root)
                    {
						if (path.size() > m_max_path.size()){
							m_max_path = path;
						}
						return;
					}
	
                    bool bUnique = std::find(path.begin(), path.end(), root->value) == path.end();
                    
                    path.push_back(root->value);

					FindLonghestDistinctPath(root->left, bUnique ? path : std::vector<int>() = { });
					FindLonghestDistinctPath(root->right, bUnique ? path : std::vector<int>() = { });

                    path.pop_back();
				}
                
			private:
				Node *m_root;
				std::vector<int> m_max_path;
		};
	}
}