#pragma once

namespace junk
{
    namespace union_intersection_array_probe_a
    {
        /*!
            input arrays should be sorted not duplicates and not null.
            results writes to out vector

            Ex.  A[] = {1, 3, 4, 5, 7}
                 B[] = {2, 3, 5, 6}

            Union: {1, 2, 3, 4, 5, 6, 7}
        */
        template<typename T>
        void Union(int A[], int n, int B[], int m, std::vector<int> &out)
        {
            if (A && B)
            {
                int i = 0;
                int j = 0;

                while (i < n && j < m)
                {
                    if (A[i] < B[j])
                    {
                        out.push_back(A[i]);
                        i++;
                    }
                    else if (A[i] > B[j])
                    {
                        out.push_back(B[j]);
                        j++;
                    }
                    else { // is equivalent
                        out.push_back(A[i]);
                        i++;
                        j++;
                    }
                }

                while (i < n){
                    out.push_back(A[i++]);
                }
                while (j < m){
                    out.push_back(B[j++]);
                }
            }            
        }

        /*!
        input arrays should be sorted not duplicates and not null.
        results writes to out vector

        Ex.  A[] = {1, 3, 4, 5, 7}
             B[] = {2, 3, 5, 6}

        Intersection: {3, 5}
        */

        template<typename T>
        void Intersection(int A[], int n, int B[], int m, std::vector<int> &out)
        {
            if (A && B)
            {
                int i = 0;
                int j = 0;

                while (i < n && j < m)
                {
                    if (A[i] < B[j])
                    {
                        i++;
                    }
                    else if (A[i] > B[j])
                    {
                        j++;
                    }
                    else if (A[i] == B[j])
                    {
                        out.push_back(A[i]);
                        i++;
                        j++;
                    }
                }
            }
        }
    }
}