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

    namespace qsort_probe_d
    {
        template<typename T>
        void qsort(int *data, int start, int len)
        {
            if (len <= 1) {
                return;
            }

            int mid = start + (len / 2);
            int key = data[mid];

            int end = start + len;
            int curr = start;

            std::swap(data[mid], data[--end]);

            while (curr < end)
            {
                if (data[curr] > key) {
                    std::swap(data[curr], data[--end]);
                }
                else {
                    curr++;
                }
            }

            std::swap(data[end], data[start + (len - 1)]);

            qsort<T>(data, start, end - start);
            qsort<T>(data, end + 1, (start + len) - (end + 1));
        }
    }
}