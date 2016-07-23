#pragma once

namespace junk
{
    /*!
    * linearize list
    */
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

    template<class T_CLASS>
    void delinearize_subsequent(T_CLASS *child)
    {
        if (!child->prev()){
            return; // feather list already splitted
        }
        child->prev()->set_next(nullptr);
        child->set_prev(nullptr);

        for (T_CLASS *curr = child; curr; curr = curr->next())
        {
            if (T_CLASS *child = curr->child()) {
                delinearize_subsequent(child);
            }
        }
    }

    /*!
    * de-linearize list
    */
    template<class T_CLASS>
    void delinearize_list(T_CLASS *head, T_CLASS **tail)
    {
        if (head && *tail)
        {
            T_CLASS *curr = head;
            *tail = nullptr;

            for (curr = head; curr; curr = curr->next())
            {
                if (T_CLASS *child = curr->child()){
                    delinearize_subsequent(child);
                }
                *tail = curr;
            }
        }
    }
}