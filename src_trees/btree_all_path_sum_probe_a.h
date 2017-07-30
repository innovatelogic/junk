#pragma once

#include <queue>

namespace junk
{
	namespace btree_all_path_sum_probe_a
	{
		struct Node
		{
			Node(int value, Node *left = nullptr, Node *right = nullptr)
                : value(value), left(left), right(right){}
			int value;
			Node *left;
			Node *right;
		};
		
		class BinaryTree
		{
			public:
                BinaryTree(Node *root)
				: m_root(root){}
				
				~BinaryTree() { clear(); }
			
				Node* root() { return m_root; }
				
				void clear()
				{
					std::queue<Node*> q;
					if (m_root)
					{
						q.push(m_root);
						while(!q.empty())
						{
							Node *front = q.front();
							q.pop();
							
							if (front->left){
								q.push(front->left);
							}
							if (front->right){
								q.push(front->right);
							}
						}
					}
				}
				
				std::vector<std::vector<Node*>> path_sum(int sum)
				{
					std::vector<std::vector<Node*>> out;
					std::vector<Node*> path;
					
                    path_sum_check(m_root, sum, path, out);
                    return out;
				}
				
				void path_sum_check(Node *root, int sum, std::vector<Node*> &path,
                                    std::vector<std::vector<Node*> > &out)
				{
					if (!root){
						return; 
					}
					
					path.push_back(root);
					
					int count = check_sum(path, sum);
					if (count > 0)
					{
						std::vector<Node*> v;
						for (int i = 0; i < count; i++){
							v.insert(v.begin(), path[(path.size() - 1) - i]);
						}
						out.push_back(v);
					}
					
					path_sum_check(root->left, sum, path, out);
					path_sum_check(root->right, sum, path, out);
					
					path.pop_back();
				}
			
                int check_sum(std::vector<Node*> &path, int sum)
                {
                    int count = 0;
                    for (int i = path.size() - 1; i >= 0; i--)
                    {
                        count += path[i]->value;
                        if (count == sum) {
                            return path.size() - i;
                        }
                    }
                    return 0;
                }
			private:
				Node *m_root;
		};
	}
}