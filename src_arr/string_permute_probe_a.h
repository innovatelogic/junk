#pragma once

namespace junk
{
    namespace string_permute_probe_a
    {
        template<typename T>
        void str_permute(T soFar, T rest, std::vector<T> &result)
        {
            if (rest.empty())
            {
                result.push_back(soFar);
            }
            else
            {
                for (size_t i = 0; i < rest.size(); i++)
                {
                    T next = soFar + rest[i];
                    T remaining = rest.substr(0, i) + rest.substr(i+1);
                    str_permute(next, remaining, result);
                }
            }
        }
    }
}