#pragma once

#include "defexport.h"
#include <vector>
#include <algorithm>
#include <set>

namespace junk
{
    namespace two_sum_problem
    {
        template<typename>
        JUNK_EXPORT bool TwoSumProblem(std::vector<int> &in, int sum, int &i_out, int &j_out)
        {
            bool bResult = false;

            if (in.size() > 1)
            {
                std::sort(in.begin(), in.end());

                std::vector<int>::const_iterator liter = in.begin();
                std::vector<int>::const_iterator riter = in.end() - 1;

                while (liter != riter)
                {
                    int curr_sum = *liter + *riter;

                    if (curr_sum < sum)
                    {
                        liter++;
                    }
                    else if (curr_sum > sum)
                    {
                        riter--;
                    }
                    else {
                        i_out = *liter;
                        j_out = *riter;
                        bResult = true;
                        break;
                    }
                }
            }
            return bResult;
        }

        template<typename>
        JUNK_EXPORT bool TwoSumProblemHash(std::vector<int> &in, int sum, int &i_out, int &j_out)
        {
            bool bResult = false;

            std::set<int> hmap;
            for (std::vector<int>::iterator iter = in.begin(); iter != in.end(); ++iter){
                hmap.insert(*iter);
            }

            for (std::vector<int>::iterator iter = in.begin(); iter != in.end(); ++iter)
            {
                std::set<int>::const_iterator fiter = hmap.find(sum - *iter);
                if (fiter != hmap.end())
                {
                    i_out = *iter;
                    j_out = *fiter;
                    bResult = true;
                    break;
                }
            }
            return bResult;
        }
    }
}