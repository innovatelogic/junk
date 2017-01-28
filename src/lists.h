#pragma once

#include "defexport.h"

namespace junk
{
    namespace lists
    {
        template<class T>
        struct JUNK_EXPORT ListNode
        {
            T value;
            ListNode *next;

            ListNode(T val, ListNode *nxt = nullptr)
                : value(val)
                , next(nxt)
            {}
        };

        template<class T_VAL, class T = ListNode<T_VAL> >
        class JUNK_EXPORT List
        {
        public:
            List()
                : m_head(nullptr)
            {}

            ~List()
            {
                Clear();
            }

            void PushBack(T_VAL val)
            {
                if (!m_head)
                {
                    m_head = new T(val);
                }
                else
                {
                    // localize end
                    T *iter = m_head;
                    while (iter->next) {
                        iter = iter->next;
                    }
                    iter->next = new T(val);
                }
            }

            void Remove(T *node)
            {
                if (!node) {
                    return;
                }

                if (node == m_head)
                {
                    m_head = m_head->next;
                    delete m_head;
                    return;
                }

                T *iter = m_head;
                while (iter->next)
                {
                    if (iter->next == node)
                    {
                        T *right = iter->next->next;
                        delete iter->next;
                        iter->next = right;
                        return;
                    }

                    iter = iter->next;
                }
            }

            void Clear()
            {
                T *iter = m_head;

                while (iter)
                {
                    T *next = iter->next;

                    delete iter;

                    iter = next;
                }
                m_head = nullptr;
            }

            ListNode<T_VAL>* head() const { return m_head; }

        private:
            T *m_head;
        };
    }
}