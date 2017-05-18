#pragma once

#include "defexport.h"
#include "lists.h"
#include <stack>

namespace junk
{
    namespace list_is_palindrome
    {
        template<class T_VAL, class T = lists::ListNode<T_VAL> >
        class JUNK_EXPORT ListExt : public lists::List<T_VAL, T>
        {
        public:
            bool IsPalindrome()
            {
                bool res = false;

                if (m_head)
                {
                    std::stack<T*> stack;

                    T *iter_slow = m_head;
                    T *iter_fast = iter_slow->next;

                    while (iter_fast)
                    {
                        stack.push(iter_slow);

                        if (!iter_fast->next){
                            break;
                        }

                        iter_fast = iter_fast->next->next;
                        iter_slow = iter_slow->next;
                    }

                    res = true;

                    if (stack.size() > 1)
                    {
                        iter_slow = iter_slow->next; // odd size scenario. move to mid + 1 element

                        while (iter_slow)
                        {
                            T *top = stack.top();

                            stack.pop();

                            if (top->value != iter_slow->value) {

                                res = false;
                                break;
                            }

                            iter_slow = iter_slow->next;
                        }
                    }
                }
                return res;
            }
        };
    }
}