#pragma once
#include <unordered_map>

namespace junk
{
    namespace string_find_first_unique_probe_a
    {
        template<typename>
        int findFirstUniqueIndex(const std::string &str)
        {
            std::unordered_map<char, int> hmap;

            const int size = str.size();
            for (int i = 0; i < size; ++i) // O(n)
            {
                if (hmap.find(str.at(i)) == hmap.end()){ // avg O(1) lookup 
                    hmap[str.at(i)] = 1;
                }
                else{
                    hmap[str.at(i)]++;
                }
            }

            for (int i = 0; i < size; ++i){ // O(n)
                if (hmap[str.at(i)] == 1){
                    return i;
                }
            }
            return -1;
        }

    }
}