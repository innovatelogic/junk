#pragma once

namespace junk
{
    namespace merge_sort_probe_c
    {
        template<typename T>
        void merge(int *data, int *tmp, int l, int llen, int r, int rlen)
        {
            int lidx = 0;
            int ridx = 0;
            int didx = 0;

            while (lidx < llen && ridx < rlen)
            {
                tmp[didx++] = data[l + lidx] < data[r + ridx] ? data[l + lidx++] : data[r + ridx++];
            }

            if (lidx < llen) {
                for (int i = lidx; i < llen; i++) {
                    tmp[didx++] = data[l + i];
                }
            }
            if (ridx < rlen) {
                for (int i = ridx; i < rlen; i++) {
                    tmp[didx++] = data[r + i];
                }
            }
        }

        template<typename T>
        void merge_sort_impl(int *data, int *tmp, int start, int len)
        {
            if (len <= 1) {
                return;
            }
            if (len == 2)
            {
                if (data[start] > data[start + 1]) {
                    std::swap(data[start], data[start + 1]);
                }
                return;
            }

            int mid = len / 2;
            merge_sort_impl<T>(data, tmp, start, len / 2); // 0 1 2 3 4
            merge_sort_impl<T>(data, tmp, start + len / 2, len - (len / 2));
            merge<T>(data, tmp, start, len / 2, start + len / 2, len - (len / 2));
            memcpy(static_cast<void*>(data + start), static_cast<void*>(tmp), sizeof(int) * len);
        }

        template<typename T>
        void merge_sort(int *data, int *tmp, int len)
        {
            if (!data || !tmp || len == 0) {
                return;
            }
            merge_sort_impl<T>(data, tmp, 0, len);
        }
    }
}