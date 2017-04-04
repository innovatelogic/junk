
#pragma once

#include <queue>
#include <vector>

namespace junk
{
    namespace bst_max_width
    {
        struct Node
        {
            Node(int value) : value(value), left(nullptr), right(nullptr) {}
            int value;
            Node *left;
            Node *right;
        };

        class BSTree
        {
        public:
            BSTree() : m_root(nullptr) {}
            ~BSTree() { clear(); }

            void insert(int value)
            {
                if (!m_root) {
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
                        else
                        {
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

            size_t max_width()
            {
                size_t width = 0;

                if (m_root)
                {
                    std::vector<Node*> v;

                    v.push_back(m_root);
                    while (!v.empty())
                    {
                        if (v.size() > width) {
                            width = v.size();
                        }

                        std::vector<Node*> new_vec;
                        for (size_t i = 0; i < v.size(); ++i)
                        {
                            if (v[i]->left) {
                                new_vec.push_back(v[i]->left);
                            }
                            if (v[i]->right) {
                                new_vec.push_back(v[i]->right);
                            }
                        }
                        v = new_vec;
                    }

                }

                return width;
            }

        private:
            Node *m_root;
        };
    }
}