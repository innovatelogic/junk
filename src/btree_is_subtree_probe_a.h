#pragma once

#include <queue>

namespace junk
{
	namespace btree_is_subtree
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
				
				bool is_subequal(BinaryTree &other)
				{
					return preorder_traverse_check(m_root, other.root());
				}
				
				bool preorder_traverse_check(const Node *root, const Node *root_other)
				{
					if (!root || !root_other){
						return false; 
					}
					
					if (root->value == root_other->value){
						if (is_subequal(root, root_other)){
							return true;
						}
					}
					
					if (preorder_traverse_check(root->left, root_other) ||
                        preorder_traverse_check(root->right, root_other)){
						return true;
					}
					return false;
				}
			
			bool is_subequal(const Node *root, const Node *root_other)
			{
                if (!root && !root_other) {
                    return true;
                }

				if ((!root && root_other) || (root && !root_other)){
					return false;
				}
				
				if (root->value != root_other->value){
					return false;
				}
				
				if (!is_subequal(root->left, root_other->left)){
					return false;
				}
				if (!is_subequal(root->right, root_other->right)){
					return false;
				}
				return true;
			}

			private:
                Node *m_root;
		};
	}
}