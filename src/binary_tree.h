#pragma once

#include <assert.h>
#include <stack>
#include <vector>

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
        class BinarySearchTree
        {
            BinarySearchTree(const BinarySearchTree &source) = delete;
            BinarySearchTree& operator=(const BinarySearchTree &source) = delete;

        public:
            BinarySearchTree()
                : m_pRoot(nullptr)
            {}

            ~BinarySearchTree()
            {
                DeallocNode(m_pRoot);
            }

            void Push(const T &value)
            {
                if (!m_pRoot) { // allocate root
                    m_pRoot = new Node<T>(value);
                }
                else { // start search descent place
                    PushImpl(m_pRoot, value);
                }
            }

            std::vector<T> GetValuesTraverseDFS()
            {
                std::vector<T> out;

                std::stack<Node<T>*> stack;

                if (m_pRoot)
                {
                    stack.push(m_pRoot);

                    while (!stack.empty())
                    {
                        Node<T> *top = stack.top();

                        stack.pop();

                        out.push_back(top->value);

                        if (top->right) {
                            stack.push(top->right);
                        }
                        if (top->left) {
                            stack.push(top->left);
                        }
                    }
                }

                
                return out;
            }

        protected:
            void PushImpl(Node<T> *node, const T &value)
            {
                assert(node);

                if (value < node->value) // insert lhs
                { 
                    if (node->left) {
                        PushImpl(node->left, value);
                    } 
                    else { 
                        node->left = new Node<T>(value); 
                    }
                }
                else // insert rhs
                { 
                    if (node->right) {
                        PushImpl(node->right, value);
                    }
                    else {
                        node->right = new Node<T>(value); 
                    }
                }
            }

        private:
            void DeallocNode(Node<T> *node)
            {
                if (node == nullptr) return;

                if (node->right) { DeallocNode(node->right); }
                if (node->left) { DeallocNode(node->left); }

                delete node;
            }
        private:
            Node<T> *m_pRoot;
        };
    }
}