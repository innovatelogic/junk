
#pragma once

#include "defexport.h"
#include "custom_list.h"

namespace junk
{
    template<class CLASS_T>
    JUNK_EXPORT ListElement<CLASS_T>* FindListNthFromEnd(List<CLASS_T> *list, int n)
    {
        ListElement<CLASS_T> *found = nullptr;

        if (list)
        {
            ListElement<CLASS_T> *forward_runner = list->head();

            // 1 2 3 4
            // need at least one iteration forward_runner
            for (int i = 0; i <= n; ++i)
            {
                forward_runner = forward_runner->next();

                if (!forward_runner) {
                    return i == n ? list->head() : nullptr; // i == n than list size equal n
                }
            }

            ListElement<CLASS_T> *back_runner = list->head();

            while (forward_runner)
            {
                forward_runner = forward_runner->next();
                back_runner = back_runner->next();
            }

            found = back_runner;
        }
        return found;
    }

 /*   JUNK_EXPORT void TestListNthFromEnd()
    {
        List<int*> lst;

        lst.InsertFront(new int(1));
        lst.InsertFront(new int(2));
        lst.InsertFront(new int(3));
        lst.InsertFront(new int(4));

        //ListElement<int*> *element0 = FindListNthFromEnd(&lst, 0);
        //ListElement<int*> *element1 = FindListNthFromEnd(&lst, 1);
        //ListElement<int*> *element2 = FindListNthFromEnd(&lst, 2);
        ListElement<int*> *element3 = FindListNthFromEnd(&lst, 3);
        ListElement<int*> *element4 = FindListNthFromEnd(&lst, 4);
    }*/
}
