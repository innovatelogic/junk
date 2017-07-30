#include <stack>
#include <queue>

namespace junk
{
	namespace bst_tree_probe_b
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
			
			~BSTree() { clear(); }
			
			void push(int value)
			{
				if (!m_root){ m_root = new SNode(value);}
				else
				{
					SNode *iter = m_root;
					while(iter)
					{
						if (value < iter->value){
							if (!iter->left){
								iter->left = new SNode(value);
								return;
							}
							iter = iter->left;
						}
						else
						{
							if (!iter->right){
								iter->right = new SNode(value);
								return;
							}
							iter = iter->right;
						}
					}
				}
			}
			
			bool is_balanced()
			{
				if (!m_root){
					return false;
				}
				
				return is_balanced(m_root) != -1;
			}
			
			void clear()
			{
				if (m_root)
				{
					std::queue<SNode*> q;
					q.push(m_root);
					
					while(!q.empty())
					{	
						SNode *top = q.front();
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
		protected:
			int is_balanced(SNode *root)
			{
				if (!root){
					return 0;
				}
				
                int lhs = is_balanced(root->left);
                if (lhs == -1) {
                    return -1;
                }
				
				
				int rhs = is_balanced(root->right);
				if (rhs == -1){
					return -1;
				}
				
				if (std::abs(rhs - lhs) > 1){
					return -1;
				}
				
				return std::max(rhs, lhs) + 1;
			}
		private:
            SNode *m_root;
		};
	}
}