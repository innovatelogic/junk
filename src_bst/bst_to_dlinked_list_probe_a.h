#pragma once

#include <queue>

namespace junk
{
	namespace binary_tree_to_dlinked_list_probe_a
	{
		struct Node{
			Node(int data) : data(data), left(nullptr), right(nullptr){}
			int data;
			Node *left;
			Node *right;
        };

		class BSTree
		{
			public:
				BSTree() : m_root(nullptr){}
				~BSTree() { /*clear();*/}
				
				void insert(int data)
				{
					if (!m_root){
						m_root = new Node(data);
					}
                    else
                    {
						Node *iter = m_root;
						while (iter)
						{
							if (data < iter->data)
                            {
								if (iter->left){
									iter = iter->left;
									continue;
								}
								iter->left = new Node(data);
								return;
							}
                            else
                            {
								if (iter->right){
									iter = iter->right;
									continue;
								}
								iter->right = new Node(data);
								return;
							}
						}
					}
				}
				
				Node* to_dlist()
				{
                    Node *head = nullptr;
					if (m_root){
						convert_l(m_root->left, m_root);
						convert_r(m_root->right, m_root);
                        
                        head = m_root;
                        while (head->left){
                            head = head->left;
                        }
					}
                    return head;
				}
				
				void convert_l(Node *node, Node *parent)
				{
					if (!node){
						return;
					}
					
					Node *l = node->left;
					Node *r = node->right;
					
					if (parent->left == node){
						node->right = parent;
					}
					else{
						Node *parent_lhs = parent->left;
						parent_lhs->right = node;
						node->left = parent_lhs;
						parent->left = node;
						node->right = parent;
					}
					convert_l(l, node);
					convert_l(r, parent);
				}
				
				void convert_r(Node *node, Node *parent)
				{
					if (!node){
						return;
					}
					
					Node *l = node->left;
					Node *r = node->right;
					
					if (parent->right == node){
						node->left = parent;
					}
					else{
						Node *parent_rhs = parent->right;
						parent_rhs->left = node;
						node->right = parent_rhs;
						parent->right = node;
						node->left = parent;
					}
					convert_r(l, parent);
					convert_r(r, node);
				}
				
				void clear()
				{
					if (m_root)
					{
						std::queue<Node*> q;
						q.push(m_root);
					
						while (!q.empty())
						{
							Node *top = q.front();
							q.pop();
							
							if (top->left){
								q.push(top->left);
							}
							if (top->right){
								q.push(top->right);
							}
						}							
					}
				}
            private:
                Node *m_root;
		};
	}
}