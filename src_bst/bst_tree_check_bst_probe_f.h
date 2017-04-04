
#pragma once

#include <queue>
#include <limits.h>

namespace junk
{
    namespace bst_tree_is_bst_probe_f
    {
        struct Node
        {
            Node(int value)
                : value(value)
                , left(nullptr)
                , right(nullptr) {}
            int value;
            Node *left;
            Node *right;
        };

        class BSTree
        {
        public:
            BSTree()
                : m_root(nullptr) {}

            ~BSTree() { clear(); }

            void insert(int value)
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
                        if (value < iter->value) {
                            if (!iter->left) {
                                iter->left = new Node(value);
                                return;
                            }
                            iter = iter->left;
                        }
                        else {
                            if (!iter->right) {
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
                std::queue<Node*> q;
                if (!m_root)
                {
                    q.push(m_root);
                    while (!q.empty())
                    {
                        Node *top = q.front();
                        q.pop();

                        if (top->left) {
                            q.push(top->left);
                        }
                        if (top->right) {
                            q.push(top->right);
                        }
                    }
                }
            }

            bool is_bst() { return is_bst(m_root, INT_MIN, INT_MAX); }

            //private:
            bool is_bst(Node *root, int min, int max)
            {
                if (!root) {
                    return true;
                }

                if (!(min < root->value && root->value < max)){
                    return false;
                }

                return is_bst(root->left, min, root->value) &&
                    is_bst(root->right, root->value - 1, max); // set min bound (root->value - 1) is to allow duplicates on a right side
            }

            // private:
            Node *m_root;
        };
    }
}