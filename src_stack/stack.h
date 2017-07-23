#pragma once

#include "defexport.h"
#include <vector>
#include <assert.h>

namespace junk
{
    namespace stack
    {
        template<class T>
        struct STACK_EXPORT StackNode
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
        class STACK_EXPORT Stack
        {
        public:
            typedef typename T_Node node_type;

            Stack()
                : m_top(nullptr)
                , m_size(0)
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
                    m_size++;
                    return;
                }
                
                new_node->next = m_top;

                m_top = new_node;
                m_size++;
            }

            void PushBack(T_VAL val)
            {
                if (!m_top)
                {
                    PushBack(val);
                    return;
                }

                T_Node *iter = m_top;
                while (iter->next)
                {
                    iter = iter->next;
                }

                T_Node *new_node = new T_Node(val);
                iter->next = new_node;
            }

            void Pop()
            {
                T_Node *next_top = m_top->next;

                delete m_top;

                m_top = next_top;

                m_size--;
            }


            void PopBack()
            {
                if (m_size <= 1)
                {
                    Pop();
                    return;
                }

                T_Node *prev = m_top;
                T_Node *iter = m_top->next;

                assert(prev && iter);

                while (iter->next)
                {
                    prev = iter;
                    iter = iter->next;
                }

                delete iter;
                prev->next = nullptr;
                m_size--;
            }

            T_Node* Top() const { return m_top; }

            size_t Size() const { return m_size; }

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

                m_size = 0;
            }

        protected:
        private:
            T_Node *m_top;
            size_t m_size;
        };
    }
}