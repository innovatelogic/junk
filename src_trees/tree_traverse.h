#pragma once
#include <functional>

namespace junk
{
    namespace tree_traverse
    {
        template<typename T>
        struct Node
        {
            Node(T val)
                : value(val)
            , left(nullptr)
            , right(nullptr){}

            T value;
            Node *left;
            Node *right;
        };

        template<typename T>
        class BTree
        {
        public:
            BTree(Node<T> *root)
                : m_root(root)
            {}

            void traverse_preorder(const std::function<void(const T &out)> &func)
            {
                traverse_preorder_impl(m_root, func);
            }

            void traverse_inorder(const std::function<void(const T &out)> &func)
            {
                traverse_inorder_impl(m_root, func);
            }

            void traverse_postorder(const std::function<void(const T &out)> &func)
            {
                traverse_postorder_impl(m_root, func);
            }
        protected:

            void traverse_preorder_impl(Node<T> *root, const std::function<void(const T &out)> &func)
            {
                if (!root) {
                    return;
                }

                func(root->value);

                traverse_preorder_impl(root->left, func);
                traverse_preorder_impl(root->right, func);
            }

            void traverse_inorder_impl(Node<T> *root, const std::function<void(const T &out)> &func)
            {
                if (!root) {
                    return;
                }

                traverse_inorder_impl(root->left, func);

                func(root->value);

                traverse_inorder_impl(root->right, func);
            }

            void traverse_postorder_impl(Node<T> *root, const std::function<void(const T &out)> &func)
            {
                if (!root) {
                    return;
                }

                traverse_postorder_impl(root->left, func);
                traverse_postorder_impl(root->right, func);

                func(root->value);
            }

        private:
            Node<T> *m_root;
        };
    }
}