#pragma once

namespace junk
{
    namespace tree_is_balanced
    {
        struct Node
        {
            Node *left;
            Node *right;
        };

        template<typename T = Node>
        class BTree
        {
        public:
            BTree(T *root)
                : m_root(root)
            {}

            T* root() { return m_root; }

            bool isBalanced() const { return m_root ? balanced(m_root) != -1 : false; }

            int getHeight() const { return height(m_root); }

        protected:
        private:

            // returns -1 if tree is not balanced otherwise positive number (tree height) 
            int balanced(T *root) const
            {
                if (!root) {
                    return 0;
                }

                int l_h = balanced(root->left);
                if (l_h == -1){
                    return -1; // height violation break
                }
                int r_h = balanced(root->right);
                if (r_h == -1) {
                    return -1; // height violation break
                }

                if (std::abs(l_h - r_h) > 1) {
                    return -1;
                }

                return std::max(l_h, r_h) + 1;
            }

            int height(T *root)
            {
                if (!root) {
                    return 0;
                }
                return std::max(height(root->left), height(root->right)) + 1;
            }

        private:
            Node *m_root;
        };
    }
}