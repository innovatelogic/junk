#pragma once

namespace junk
{
    template<class T_CLASS>
    void flatten_list(T_CLASS *head, T_CLASS **tail)
    {
        T_CLASS *iter = head;

        while (iter)
        {
            if (T_CLASS *child = iter->child())
            {
                (*tail)->set_next(child);
                child->set_prev(*tail);

                while (child)
                {
                    T_CLASS *next = child->next();

                    if (!next)
                    {
                        (*tail) = child;
                        break;
                    }
                    child = next;
                }
            }

            iter = iter->next();
        }
    }
}