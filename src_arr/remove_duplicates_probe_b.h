#pragma once

namespace junk
{
    namespace remove_duplicates_probe_b
    {
        template<class T>
        void myqsort(T *array, int start, int length)
        {
            if (!array) {
                return;
            }

            if (length < 2) { return; }

            int curr = start;
            int mid = start + length / 2;
            int key = array[mid];
            int end = start + length;

            std::swap(array[mid], array[--end]);

            while (curr < end)
            {
                if (array[curr] < key)
                {
                    curr++;
                }
                else
                {
                    std::swap(array[curr], array[--end]);
                }
            }

            std::swap(array[end], array[start + length - 1]);

            int llen = end - start;
            int rlen = length - llen - 1;

            myqsort(array, start, llen);
            myqsort(array, end + 1, rlen); // ((start + len - 1) - (end + 1) + 1) -> 
                                                               // (start + len - 1 - end - 1 + 1) ->
                                                               //  start + len - mid - 1
        }


        template<typename T>
        int RemoveDuplicates(T *array, int length)
        {
            if (!array || length <= 1) {
                return -1;
            }

            myqsort(array, 0, length);
            
            // j
            //   i
            // 1 1 2 2 3 3 
            int j = 0;
            for (int i = 1; i < length;)
            {
                if (array[j] == array[i]){
                    i++;
                }
                else{
                    array[++j] = array[i++];
                }
            }
            return j + 1;
        }
    }
}