#pragma once 

namespace junk
{
    namespace qsort_probe_a
    {
        template<typename T>
        void myqsort(T *base, int i, int len)
        {
            if (len <= 1) {
                return;
            }

            int mid = i + len / 2;
            int curr = i;
            int end = i + len;

            int pivot = base[mid];

            std::swap(base[mid], base[--end]);

            while (curr < end)
            {
                if (base[curr] > pivot)
                {
                    std::swap(base[curr], base[--end]);
                }
                else{
                    curr++;
                }
            }

            std::swap(base[end], base[i + len - 1]);

            myqsort(base, i, end - i);
            myqsort(base, end + 1, len - (end + 1));
        }
    }

}