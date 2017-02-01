#pragma once

#include "defexport.h"

namespace junk
{
    namespace stack
    {
        template<class T>
        struct JUNK_EXPORT StackNode
        {
            T value;
            StackNode *next;

            StackNode(T val)
                : value(val)
                , next(nullptr)
            {
            }
        };

        template<class T_VAL, class T_Node = StackNode<T_VAL> >
        class JUNK_EXPORT Stack
        {
        public:
            Stack()
                : m_top(nullptr)
            {}

            virtual ~Stack()
            {
                Clear();
            }

            void Push(T_VAL val)
            {
                T_Node *new_node = new T_Node(val);

                if (!m_top)
                {
                    m_top = new_node;
                    return;
                }
                
                new_node->next = m_top;
                m_top = new_node;
            }

            void Pop()
            {
                T_Node *next_top = m_top->next;

                delete m_top;

                m_top = next_top;
            }

            T_Node* Top() const { return m_top; }

            void Clear()
            {
                T_Node *iter = m_top;

                while (iter)
                {
                    T_Node *next = iter->next;

                    delete iter;

                    iter = next;
                }

                m_top = nullptr;
            }

        protected:
        private:
            T_Node *m_top;
        };
    }
}