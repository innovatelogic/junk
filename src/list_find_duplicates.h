#pragma once

#include "defexport.h"
#include "lists.h"
#include <set>

namespace junk
{
    namespace list_find_duplicates
    {
        template<class T_VAL, class T = lists::ListNode<T_VAL> >
        class JUNK_EXPORT ListExt : public lists::List<T_VAL, T>
        {
        public:
            void ClearDuplicates()
            {
                std::set<T_VAL> set;

                T *iter = head();

                if (iter)
                {
                    set.insert(iter->value);

                    while (iter->next)
                    {
                        if (set.find(iter->next->value) != set.end())
                        {
                            T *right = iter->next->next;

                            delete iter->next;

                            iter->next = right;

                            continue;
                        }
                        
                        set.insert(iter->next->value);
                        
                        iter = iter->next;
                    }
                }
            }

           /* ListNode<T_VAL>* FindKthFromEnd(size_t k)
            {
                ListNode<T_VAL> *out = nullptr;

                ListNode<T_VAL> *iter = m_head;
                for (size_t i = 0; i < k; i++)
                {
                    iter = iter->next;

                    if (!iter) {
                        return nullptr;
                    }
                }

                out = m_head;
                while (iter)
                {
                    out = out->next;
                    iter = iter->next;
                }
                
                return out;
            }*/
        };
    }
}