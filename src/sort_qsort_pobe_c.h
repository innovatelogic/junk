#pragma once

namespace junk
{
    namespace qsort_probe_c
    {
        template<typename T>
        void qsort_c(int *data, int start, int len)
        {
            if (len <= 1) {
                return;
            }

            int curr = start;
            int end = start + len;
            int mid = start + len / 2;

            int pivot = data[mid];

            std::swap(data[mid], data[--end]);

            while (curr < end)
            {
                if (data[curr] > pivot) {
                    std::swap(data[curr], data[--end]);
                }
                else {
                    curr++;
                }
            }

            std::swap(data[end], data[start + len - 1]);

            qsort_c<T>(data, start, end - start);
            qsort_c<T>(data, end + 1, len - (end + 1));
        }
    }
}