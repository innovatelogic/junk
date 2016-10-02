#pragma once

namespace junk
{
    namespace binary_tree
    {
        template<class T>
        struct Node
        {
            Node (T val, Node *lhs = nullptr, Node *rhs = nullptr)
                : value(val)
                , left(lhs)
                , right(rhs)
            {}

            T value;
            Node *left;
            Node *right;
        };

        template<class T>
        class BinaryTree
        {
            BinaryTree(const BinaryTree &source) = delete;
            BinaryTree& operator=(const BinaryTree &source) = delete;

        public:
            BinaryTree()
                : m_pRoot(nullptr)
            {}

        protected:
        private:
            Node<T> *m_pRoot;
        };
    }
}