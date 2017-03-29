#pragma once
#include <vector>

namespace junk
{
	namespace isertion_sort_probe_b
	{
		template<typename T>
		void insertion_sort(std::vector<int> &in)
		{
			for (size_t which = 1; which < in.size(); ++which)
			{
				for (size_t i = 0; i < which; ++i)
				{
					int value = in[which];
					
					if (value < in[i])
					{
						for (size_t k = which; k > i; k--){
							in[k] = in[k - 1];
						}
						in[i] = value;
						break;
					}
				}
			}
			
		}
	}
}