
#pragma once
#include "defexport.h"

namespace junk
{
    namespace stack_sort
    {
        template<class T_CONT>
        JUNK_EXPORT void stack_sort(T_CONT &stack)
        {
            if (!stack.empty())
            {
                T_CONT tmp_stack;

                tmp_stack.push(stack.top());

                stack.pop();

                while (!stack.empty())
                {
                    T_CONT::value_type top = stack.top();
                    stack.pop();

                    int n_count = 0;

                    while (!tmp_stack.empty())
                    {
                        if (tmp_stack.top() < top)
                        {
                            stack.push(tmp_stack.top());
                            tmp_stack.pop();
                            n_count++;
                            continue;
                        }
                        break;
                    }

                    tmp_stack.push(top);

                    while (n_count)
                    {
                        tmp_stack.push(stack.top());
                        stack.pop();
                        n_count--;
                    }
                }

                stack = tmp_stack;
            }
        }
    }
}