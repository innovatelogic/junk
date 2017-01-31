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

            int operator+(const ListExt &second)
            {
                int out = 0;

                lists::ListNode<int> *iter_a = head();
                lists::ListNode<int> *iter_b = second.head();

                int shift = 0;
                int mult = 1;

                while (iter_a || iter_b)
                {
                    int val = shift;
                    
                    if (iter_a) {
                        val += iter_a->value;
                    }
                    if (iter_b) {
                        val += iter_b->value;
                    }

                    shift = 0;
                    if (val >= 10)
                    {
                        val %= 10;
                        shift = 1;
                    }
                    
                    out = out + (val * mult);
                    mult *= 10;

                    if (iter_a) {
                        iter_a = iter_a->next;
                    }

                    if (iter_b) {
                        iter_b = iter_b->next;
                    }
                }

                return out;
            }


            int operator^(const ListExt &second)
            {
                int out = 0;

                std::stack<lists::ListNode<int>*> stack_a;
                std::stack<lists::ListNode<int>*> stack_b;

                lists::ListNode<int> *iter_a = head();
                lists::ListNode<int> *iter_b = second.head();
                
                while (iter_a || iter_b)
                {
                    if (iter_a) {
                        stack_a.push(iter_a);
                        iter_a = iter_a->next;
                    }
                    if (iter_b) {
                        stack_b.push(iter_b);
                        iter_b = iter_b->next;
                    }
                }

                int mult = 1;
                int carry = 0;
                while (!stack_a.empty() || !stack_b.empty())
                {
                    int v_a = 0;
                    if (!stack_a.empty())
                    {
                        v_a = stack_a.top()->value;
                        stack_a.pop();
                    }

                    int v_b = 0;
                    if (!stack_b.empty())
                    {
                        v_b = stack_b.top()->value;
                        stack_b.pop();
                    }

                    int val = carry;
                    val += v_a + v_b;

                    carry = 0;
                    if (val >= 10)
                    {
                        val %= 10;
                        carry = 1;
                    }

                    out = (val * mult) + out;
                    mult *= 10;
                }

                return out;
            }

        private:
          /*  int addDigit(lists::ListNode<int> *a, lists::ListNode<int> *b, int &shift)
            {
                int res = 0;

                if (!a && !b){
                    return 0;
                }

                res += addDigit(a ? a->next : nullptr, a ? a->next : nullptr);


            }*/
        };
    }
}