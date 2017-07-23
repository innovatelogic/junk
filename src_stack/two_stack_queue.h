
#pragma once

#include "defexport.h"
#include <stack>

namespace junk
{
    namespace two_stack_queue
    {
        template <class T>
        class STACK_EXPORT MyQueue
        {
        public:
            MyQueue()
                : m_in(new std::stack<T>())
                , m_out(new std::stack<T>())
            {}

            ~MyQueue()
            {
                delete m_in;
                delete m_out;
            }

            void push(T value)
            {
                m_in->push(value);
            }

            void push(T &value)
            {
                m_in->push(value);
            }

            void pop()
            {
                pump();
                m_out->pop();
            }

            T top()
            {
                pump();
                return m_out->top();
            }

        protected:
            void pump()
            {
                while (!m_in->empty())
                {
                    m_out->push(m_in->top());
                    m_in->pop();
                }
            }

        private:
            std::stack<T> *m_in;
            std::stack<T> *m_out;
        };
    }
}