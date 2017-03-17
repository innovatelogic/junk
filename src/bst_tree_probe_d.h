#include <queue>

namespace junk
{
	namespace bst_tree_probe_d
	{
		struct Node
		{
			Node(int val)
			: value(val)
			, left(nullptr)
			, right(nullptr){}

            Node* remove(int value, Node *parent)
            {
                if (value < this->value){
                    return left ? left->remove(value, this) : nullptr;
                }
                else if (value > this->value){
                    return right ? right->remove(value, this) : nullptr;
                }

                if (left && right)
                {
                    this->value = right->min();
                    return right->remove(this->value, this);
                }
                else if (parent->left == this)
                {
                    parent->left = left ? left : right;
                    return this;
                }
                else if (parent->right == this)
                {
                    parent->right = left ? left : right;
                    return this;
                }
                return nullptr;
            }

            int min()
            {
                if (left == nullptr) {
                    return value;
                }
                return left->min();
            }
			
			int value;
			Node *left;
			Node *right;
		};
	
		class BSTree
		{
		public:
			BSTree()
			: m_root(nullptr){}
			
			~BSTree() { clear(); }

            Node* root() { return m_root; }
			
			void push(int value)
			{
				if (!m_root)
				{
					m_root = new Node(value);
				}
				else
				{
					Node *iter = m_root;
					while(iter)
					{
						if (value < iter->value)
						{
							if (!iter->left)
							{
								iter->left = new Node(value);
								return;
							}
							iter = iter->left;
						}
						else
						{
							if (!iter->right)
							{
								iter->right = new Node(value);
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
					std::queue<Node*> q;
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
			
			int max_height() { return max_height(m_root); }
			
			int max_height(Node *root)
			{
				if (!root){
					return 0;
				}	
				return std::max(max_height(root->left), max_height(root->right)) + 1;
			}
			
			Node* findLowestCommonAncestor(Node *node1, Node *node2)
			{
				if (!node1 || !node2 || !m_root){
					return nullptr;
				}
				return findLowestCommonAncestor(node1->value, node2->value);
			}
			
			Node* findLowestCommonAncestor(int value1, int value2)
			{
				Node *iter = m_root;
				
				while(iter)
				{
					if (value1 < iter->value && value2 < iter->value)
					{
						iter = iter->left;
						continue;
					}
					else if (value1 > iter->value && value2 > iter->value)
					{
						iter = iter->right;
						continue;
					}
					
					return iter;
				}
				return nullptr;
			}
			
			bool is_balanced() { return is_balanced(m_root) != -1; }
			
			int is_balanced(Node *root)
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
				
				return std::max(rhs, lhs) + 1;
			}
			
			int distance(Node *node1, Node *node2)
			{
				if (!m_root || !node1 || !node2){
					return -1;
				}
			
				int n1 = node1->value;
				int n2 = node2->value;
			
                return distance(n1, n2);
			}

            int distance(int n1, int n2)
            {
                if (n2 < n1){
                    std::swap(n1, n2);
                }
                Node *iter = m_root;
                while (iter)
                {
                    if (n1 < iter->value && n2 < iter->value)
                    {
                        iter = iter->left;
                        continue;
                    }
                    else if (n1 > iter->value && n2 > iter->value)
                    {
                        iter = iter->right;
                        continue;
                    }

                    // find lowest common ancestor
                    int lhs = depth(iter, n1);
                    if (lhs == -1) {
                        return -1;
                    }

                    int rhs = depth(iter, n2);
                    if (rhs == -1) {
                        return -1;
                    }
                    return lhs + rhs;
                }
                return -1;
            }
			
			int depth(Node* root, int n)
			{
				int depth = 0;
				
				if (!root){
					return -1;
				}

				while (root)
				{
					if (n == root->value){
						return depth;
					}
					
					if (n < root->value){
						root = root->left;
					}
					else {
						root = root->right;
					}
					++depth;
				}
                return -1;
			}

            bool remove(int value)
            {
                if (!m_root) {
                    return false;
                }
                else
                {
                    if (m_root->value == value)
                    {
                        Node auxRoot(0);
                        auxRoot.left = m_root;
                        Node *rem = m_root->remove(value, &auxRoot);
                        m_root = auxRoot.left;
                        if (rem != nullptr)
                        {
                            delete rem;
                            return true;
                        }
                        return false;
                    }
                    else
                    {
                        Node *rem = m_root->remove(value, nullptr);
                        if (rem)
                        {
                            delete rem;
                            return true;
                        }
                        return false;
                    }
                }
            }
			
		protected:
		private:
			Node *m_root;
		};
	}
}