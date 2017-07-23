#pragma once


#include "defexport.h"
#include "stack.h"
#include <assert.h>

namespace junk
{
    namespace stack_min_track
    {
        template<typename T_VAL>
        class STACK_EXPORT StackMin : private stack::Stack<T_VAL>
        {
        public:
            StackMin()
            {
                m_stackMin = new stack::Stack<T_VAL>();
            }

            ~StackMin()
            {
                delete m_stackMin;
            }

            void Push(T_VAL val)
            {
                stack::StackNode<T_VAL>* currMin = m_stackMin->Top();

                if (!currMin)
                {
                    m_stackMin->Push(val);
                }
                else
                {
                    if (val <= currMin->value)
                    {
                        m_stackMin->Push(val);
                    }
                }

                stack::Stack<T_VAL>::Push(val);
            }

            void Pop()
            {
                stack::StackNode<T_VAL>* currMin = m_stackMin->Top();

                assert(currMin);

                stack::StackNode<T_VAL>* curr = Top();

                assert(curr);

                if (curr->value == currMin->value) {
                    m_stackMin->Pop();
                }
                stack::Stack<T_VAL>::Pop();
            }

            stack::StackNode<T_VAL>* Min() const { return m_stackMin->Top(); }

            stack::StackNode<T_VAL>* Top() const { return  stack::Stack<T_VAL>::Top(); }

        private:

            stack::Stack<T_VAL> *m_stackMin;
        };
    }
}