#pragma once

#include "defexport.h"
#include "lists.h"

namespace junk
{
    namespace list_to_int
    {
        class JUNK_EXPORT ListExt : public lists::List<int, lists::ListNode<int>>
        {
        public:
            // convert to int in forward order
            // 1 -> 2 -> 3 = 123
            int GetInt()
            {
                int out = 0;

                lists::ListNode<int> *iter = head();

                int mult = 1;
                while (iter)
                {
                    out = (out * 10) + iter->value;
                    iter = iter->next;
                }

                return out;
            }

            // convert to int in reverse order
            // 1 -> 2 -> 3 = 321
            int GetIntRev()
            {
                int out = 0;

                lists::ListNode<int> *iter = head();

                int mult = 1;
                while (iter)
                {
                    out = out + (iter->value * mult);
                    mult *= 10;
                    iter = iter->next;
                }

                return out;
            }
        };
    }

}