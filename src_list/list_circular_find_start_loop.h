#pragma once

#include "defexport.h"
#include "lists.h"
#include <stack>
#include <assert.h>

namespace junk
{
    namespace list_is_circular
    {
        template<class T_VAL, class T = lists::ListNode<T_VAL> >
        class JUNK_EXPORT ListExt : public lists::List<T_VAL, T>
        {
        public:
            T* IsCircular()
            {
                T *out = nullptr;

                T *slow = head();
                T *fast = head();

                while (fast && fast->next)
                {
                    slow = slow->next;
                    fast = fast->next->next;

                    if (!fast){
                        return false;
                    }

                    if (fast == slow) // collision
                    {
                        slow = head();

                        while (fast != slow)
                        {
                            fast = fast->next;
                            slow = slow->next;
                        }
                        out = fast;
                        break;
                    }
                }

                return out;
            }

             bool AddEndLoop(T *loop_to)
            {
                bool res = false;

               if (loop_to && head())
                {
                    T *iter = head();

                    bool bfind = false;
                    T *end = nullptr;
                    while (iter)
                    {
                        if (iter == loop_to) {
                            assert(!bfind);
                            bfind = true;
                        }
                        end = iter;
                        iter = iter->next;
                    }

                    if (bfind && end)
                    {
                        end->next = loop_to;
                        res = true;
                    }
                }
                return res;
            }
        };
    }
}