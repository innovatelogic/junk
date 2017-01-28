#pragma once

#include "defexport.h"
#include "lists.h"

namespace junk
{
    namespace list_rearrange_by_kth_element
    {
        template<class T_VAL, class T = lists::ListNode<T_VAL> >
        class JUNK_EXPORT ListExt : public lists::List<T_VAL, T>
        {
        public:
            void RearrangeByElement(T *node)
            {
                T *before = nullptr;
                T *after = nullptr;

                T *iter = head();

                while (iter != nullptr)
                {
                    T *iter_next = iter->next;

                    if (iter != node)
                    {
                        if (iter->value < node->value)
                        {
                            iter->next = before;
                            before = iter;
                        }
                        else
                        {
                            iter->next = after;
                            after = iter;
                        }
                    }

                    iter = iter_next;
                }

                node->next = after;
                after = node;

                if (before == nullptr)
                {
                    m_head = after;
                    return;
                }

                T *last = before;
                while (last->next) {
                    last = last->next;
                }

                last->next = after;

                m_head = before;
            }
        };
    }

}