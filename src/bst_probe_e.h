#pragma once

#include <queue>
#include <vector>

namespace junk
{
    namespace bst_probe_e
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
            BSTree()
                : m_head(nullptr) {}

            BSTree(std::vector<int> &array)
                : m_head(nullptr)
            {
                std::sort(array.begin(), array.end());
                build_from_sorted_array(array, 0, array.size() - 1);
            }

            ~BSTree() { clear(); }

            void insert(int value)
            {
                if (!m_head)
                {
                    m_head = new Node(value);
                }
                else
                {
                    Node *iter = m_head;
                    while (iter)
                    {
                        if (value < iter->value)
                        {
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
                if (m_head)
                {
                    q.push(m_head);
                    while (!q.empty())
                    {
                        Node *front = q.front();
                        q.pop();

                        if (front->left) {
                            q.push(front->left);
                        }
                        if (front->right) {
                            q.push(front->right);
                        }
                    }
                }
            }

            bool is_balanced()
            {
                return is_balanced(m_head) != -1;
            }

            int is_balanced(Node *root)
            {
                if (!root) {
                    return 0;
                }

                int left = is_balanced(root->left);
                if (left == -1) {
                    return left;
                }
                int right = is_balanced(root->right);
                if (right == -1) {
                    return right;
                }
                if (std::abs(left - right) > 1) {
                    return -1;
                }

                return std::max(left, right) + 1;
            }

        protected:
            void build_from_sorted_array(const std::vector<int> &in, int left, int right)
            {
                if (right < left) {
                    return;
                }

                int mid = (left + right) / 2;

                insert(in[mid]);

                build_from_sorted_array(in, left, mid - 1);
                build_from_sorted_array(in, mid + 1, right);
            }

        private:
            Node *m_head;
        };

    }
}