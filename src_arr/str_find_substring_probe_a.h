#pragma once

#include <string>

namespace junk
{
	namespace str_find_substring_probe_a
	{
        // naive implementation O(n * m)
        template<typename T>
		int substr(const std::string &str, const std::string &pattern)
		{
			const size_t str_size = str.size();
			const size_t p_size = pattern.size();
			
			if (p_size > str_size){
				return -1;
			}
			
			for (size_t i = 0; i < str_size; i++)
			{
                size_t j = 0;
				for (; j < p_size && i + j < str_size; j++)
				{
					if (str[i + j] != pattern[j]){
						break;
					}
				}
				
				if (j == p_size){
					return i;
				}
			}
			return -1;
		}
	}
}