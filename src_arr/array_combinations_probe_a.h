#pragma once

#include <string>
#include <vector>

namespace junk
{
	namespace array_combinations_probe_a
	{
		template<typename T>
		void combinations_impl(const std::string &in, size_t start, std::string &buffer, std::vector<std::string> &out)
		{
			if (start == in.size()){
				return;
			}
			
			for (size_t i = start; i < in.size(); i++)
			{
				buffer.push_back(in[i]);
				out.push_back(buffer);
				
                combinations_impl<T>(in, i + 1, buffer, out);
				buffer.pop_back();
			}
		}
		
		template<typename T>
		void combinations(const std::string &in, std::vector<std::string> &out)
		{
			std::string buffer;
            combinations_impl<T>(in, 0, buffer, out);
		}
	}
}