#pragma once
#pragma once

#include "custom_list.h"

namespace junk
{
    template<class T>
    bool IsCircularList(const ListElement<T> *head)
    {
        bool bResult = false;

        if (head && head->next())
        {
            const ListElement<T> *low = head;
            const ListElement<T> *high = head->next();

            while (high)
            {
                if (!high->next()) {
                    break;
                }

                if (low == high) 
                {
                    bResult = true;
                    break;
                }

                low = low->next();
                high = high->next()->next();
            }
        }
        return bResult;
    }
}

