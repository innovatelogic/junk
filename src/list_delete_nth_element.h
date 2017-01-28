#pragma once

#include "defexport.h"
#include "lists.h"

namespace junk
{
    namespace list_delete_nth_element
    {
        template<class T_VAL, class T = lists::ListNode<T_VAL> >
        class JUNK_EXPORT ListExt : public lists::List<T_VAL, T>
        {
        public:
            void DeleteNth(lists::ListNode<T_VAL> *node)
            {
                if (node && node->next)
                {
                    node->value = node->next->value;
                    
                    T *to_rem = node->next;
                    node->next = node->next->next;

                    delete to_rem;
                }
            }
        }
    }
}