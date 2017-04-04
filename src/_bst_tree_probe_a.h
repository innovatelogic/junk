#pragma once

namespace junk
{
	namespace bst_tree_probe_a
	{
		struct SNode
		{
			SNode(int value)
			: data(value)
			, left(nullptr)
			, right(nullptr){}
			
			int data;
			SNode *left;
			SNode *right;
		};

		class BSTTree
		{
		public:
			BSTTree()
			: m_root(nullptr){}
			
			~BSTTree()
			{
				clear();
			}
			
			void push(int value)
			{
				if (!m_root)
				{
					m_root = new SNode(value);
				}
				else
				{
					SNode *iter = m_root;
					while(iter){
						if (value < iter->data)
						{
							if (!iter->left){
								iter->left = new SNode(value);
								return;
							}
							iter = iter->left;
						}
						else{
							if (!iter->right){
								iter->right = new SNode(value);
								return;
							}
							iter = iter->right;
						}
					}
				}
			}
			
			void clear()
			{
				remove_node(m_root);
				m_root = nullptr;
			}
			
			SNode* findLowestCommonAncestor(int node1, int node2)
			{
				if (node1 > node2){
					std::swap(node1, node2);
				}
				
				SNode *iter = m_root;
				
				while (iter)
				{
					if (node1 < iter->data &&
						node2 < iter->data)
					{
						iter = iter->left;
						continue;
					}
					else if (node1 > iter->data &&
							 node2 > iter->data)
					{
						iter = iter->right;
						continue;
					}	
					return iter;
				}
				return nullptr;
			}
			
			int distance(int n1, int n2)
			{
				int out = -1;
				
				if (n2 < n1){
					std::swap(n1, n2);
				}
				
				SNode* iter = m_root;
				
				while (iter)
				{
					if (n1 < iter->data && n2 < iter->data)
					{
						iter = iter->left;
						continue;
					}
					else if (n1 > iter->data && n2 > iter->data)
					{
						iter = iter->right;
						continue;
					}
				
					SNode* lowest = iter;
					
					int dist_l = findNode(iter, n1);
					int dist_r = findNode(iter, n2);
					
					if (dist_l == -1 || dist_r == -1){
						return -1;
					}
					
					out = dist_l + dist_r;
					
					break;
				}
				return out;
			}
			
			int findNode(SNode* root, int n)
			{
				int out = 0;
				
				SNode* iter = root;
				
				while(iter)
				{
					if (iter->data == n){
						break;
					}
					
					if (n < iter->data)
					{
						iter = iter->left;
					}
					else if (n > iter->data)
					{
						iter = iter->right;
					}
					out++;
				}
				return !iter ? -1 : out;
			}
			
			size_t height()
			{
				return max_height(m_root);
			}
			
		protected:
		
			void remove_node(SNode *node)
			{
				if (!node){
					return;
				}
				
				remove_node(node->left);
				remove_node(node->right);
				
				delete node;
			}
			
			int max_height(SNode *root)
			{
				if (!root){
					return 0;
				}
				
				return std::max(max_height(root->left), max_height(root->right)) + 1; 
			}
			
		private:
			SNode *m_root;
		};
	}
}