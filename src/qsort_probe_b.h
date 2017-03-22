#pragma once 

namespace junk
{
    namespace qsort_probe_b
    {
        template<typename T>
        void _qsort_probe_b(int *data, int i, int len)
        {
            if (len <= 1) {
                return;
            }

            int mid = i + len / 2;
            int curr = i;
            int end = i + len;
            int pivot = data[mid];

            std::swap(data[mid], data[--end]); // 2 1 0 -> 2 0 1 : 1 -> 0 2 1 -> 0 1 2 

            while (curr < end)
            {
                if (data[curr] > pivot) {
                    std::swap(data[curr], data[--end]);
                }
                else {
                    curr++;
                }
            }

            std::swap(data[curr], data[i + len - 1]);

            _qsort_probe_b<T>(data, i, curr - i);
            _qsort_probe_b<T>(data, curr + 1, len - (curr + 1));
        }
    }
}