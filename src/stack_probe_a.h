#pragma once

namespace junk
{
    namespace stack_probe_a
    {
        template<typename T>
        struct Node
        {
            Node(T &value) : value(value), next(nullptr) {}
            T value;
            Node *next;
        };

        template<typename T>
        class Stack
        {
        public:
            Stack() : m_head(nullptr) {}
            ~Stack() { clear(); }

            void push(T &&val)
            {
                if (!m_head)
                {
                    m_head = new Node<T>(val);
                }
                else
                {
                    Node<T> *new_node = new Node<T>(val);
                    new_node->next = m_head;
                    m_head = new_node;
                }
            }

            void pop()
            {
                if (m_head)
                {
                    Node<T> *next = m_head->next;
                    delete m_head;
                    m_head = next;
                }
            }

            Node<T>* top() { return m_head; }

            void clear()
            {
                Node<T> *iter = m_head;
                while (iter)
                {
                    Node<T> *next = iter->next;
                    delete iter;
                    iter = next;
                }
            }

        protected:
        private:
            Node<T> *m_head;
        };
    }
}