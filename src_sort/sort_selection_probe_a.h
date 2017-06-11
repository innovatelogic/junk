#pragma once

namespace junk
{
	namespace sort_selection_probe_a
	{
		template<typename T>
		void selection_sort(std::vector<T> &in, size_t start)
		{
			if (start < in.size())
			{
				std::swap(in[start], in[findMinIndex(in, start)]);
				selection_sort(in, start + 1);	
			}
		}
		
        template<typename T>
		size_t findMinIndex(std::vector<T> &in, size_t start)
		{
			int min_idx = start;
			
			for (size_t i = min_idx + 1; i < in.size(); i++)
			{
				if (in[i] < in[min_idx]){
					min_idx = i;
				}
			}
			
			return min_idx;
		}

        template<typename T>
        void selection_sort(std::vector<int> &in)
        {
            selection_sort(in, 0);
        }
	}
}