#pragma once
#include "stack.h"

namespace junk
{
    namespace set_of_stacks
    {
        template<class T, size_t MAX_SIZE = 3>
        class SetOfStacks
        {
        public:
            typedef typename junk::stack::Stack<junk::stack::Stack<T>> stack_type;

            SetOfStacks()
            {
                m_pStack = new stack_type();
            }

            SetOfStacks(const SetOfStacks&) = delete;

            ~SetOfStacks()
            {
                delete m_pStack;
            }

            void Push(T val)
            {
                stack_type::node_type *head = m_pStack->Top();

                if (!head || head->value.Size() == MAX_SIZE)
                {
                    // add new head
                    m_pStack->Push(junk::stack::Stack<T>());
                    head = m_pStack->Top();
                }

                assert(head);
                head->value.Push(val);
            }

            void Pop()
            {
                stack_type::node_type *head = m_pStack->Top();

                assert(head);

                head->value.Pop();

                if (head->value.Size() == 0) {
                    m_pStack->Pop();
                }
            }

            size_t Size() const {
                return m_pStack->Size();
            }

            void PopAt(size_t index)
            {
                stack_type::node_type *head = m_pStack->Top();

                while (index)
                {
                    head = head->next;
                    index--;
                }

                assert(head);

                head->value.Pop();

                if (!head->value.Size())
                {
                    m_pStack->PopBack();
                }
                else
                {
                    stack_type::node_type *iter = head;
                    while (iter->next)
                    {
                        T tmp_val = iter->next->value.Top()->value;

                        iter->next->value.Pop();

                        iter->value.PushBack(tmp_val);

                        if (iter->next->value.Size() == 0)
                        {
                            m_pStack->PopBack();
                            break;
                        }

                        iter = iter->next;
                    }
                }
            }

        protected:
        private:
            /*void ShiftLeft(stack_type::node_type *node)
            {
                if (!node->next)
                {
                    return
                }

                T tmp_val = node->next->value.Top();

                node->next->value.Pop();

                node->PushBack(tmp_val);

                if (node->next->value.Size() == 0)
                {
                    m_pStack->PopBack();
                }
                else
                {
                    ShiftLeft(node->next);
                }
            }*/
        private:

            stack_type *m_pStack;
        };
    }
}