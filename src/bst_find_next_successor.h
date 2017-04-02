#pragma once

#include <queue>

namespace junk
{
	namespace bst_find_next_successor
	{
		struct Node
		{
			Node(int value, Node *left = nullptr, Node *right = nullptr) 
                : value(value), left(left), right(right){}
			int value;
			Node *left;
			Node *right;
		};
		
		class BSTree
		{
			public:
				BSTree(Node *root)
				: m_root(root){}
				
				~BSTree() { clear(); }
			
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
				
				Node* next_node(Node *node)
				{
					if (node->right){
						return minValue(node->right);
					}
					
					Node *succ = nullptr;
					Node *iter = m_root;
					
					while (iter)
					{
						if (node->value < iter->value)
						{
							succ = iter;
							iter = iter->left;
						}
						else if (node->value > iter->value){
							iter = iter->right;
						}
						else{
							break;
						}
					}
					
					return succ;
				}
				
				Node* minValue(Node *root)
				{
					Node *iter = root;
					while (iter->left){
						iter = iter->left;
					}
					return iter;
				}
			private:
				Node *m_root;
		};
	}
}