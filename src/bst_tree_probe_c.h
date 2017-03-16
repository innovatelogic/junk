#include <queue>

namespace junk
{
	namespace bst_tree_probe_c
	{
		struct SNode
		{
			SNode(int val)
			: value(val)
            , left(nullptr)
            , right(nullptr){}
			
			int value;
			SNode *left;
			SNode *right;
		};
		
		class BSTree
		{
		public:
			BSTree()
			: m_root(nullptr){}
			
			~BSTree(){ clear(); }
			
			void push(int value)
			{
				if (!m_root)
				{
					m_root = new SNode(value);
				}
				else
				{
					SNode *iter = m_root;
					
					while (iter)
					{
						if (value < iter->value)
						{
							if (!iter->left){
								iter->left = new SNode(value);
								return;
							}
							iter = iter->left;
						}
						else
						{
							if (!iter->right)
							{
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
				if (m_root)
				{
					std::queue<SNode*> s;
					
					while (!s.empty())
					{
						SNode *top = s.front();
						s.pop();
						
						if (top->left){
							s.push(top->left);
						}
						if (top->right){
							s.push(top->right);
						}
					}
				}
			}
			
			int max_height()
			{
				return m_root ? max_height(m_root) : 0;
			}
		
			int max_height(SNode *root)
			{
				if (!root){
					return 0;
				}
				return std::max(max_height(root->left), max_height(root->right)) + 1;
			}
			
			bool is_balanced()
			{
				return m_root ? is_balanced(m_root) != -1 : false;
			}
			
			void rotate_right()
			{
				if (m_root)
				{
					SNode *old_root = m_root;
					SNode *old_left = m_root->left;
					SNode *old_left_right = old_left->right;
					
					m_root = old_left;
					m_root->right = old_root;
					old_root->left = old_left_right;
				}
			}
		protected:
			
			int is_balanced(SNode *root)
			{
				if (!root){
					return 0;
				}
				
				int lhs = is_balanced(root->left);
				if (lhs == -1){
					return -1;
				}
				
				int rhs = is_balanced(root->right);
				if (rhs == -1){
					return -1;
				}
				
				if (std::abs(lhs - rhs) > 1){
					return -1;
				}
				
				return std::max(lhs, rhs) + 1;
			}
		private:
			SNode *m_root;
		};
	}
}