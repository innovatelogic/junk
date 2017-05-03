
#pragma once

#include <stack>
#include <list>

namespace junk
{
	namespace combinations_of_sum_num
	{
		class SumsSeq
		{
			public:
				SumsSeq(unsigned int n) { generate_impl(n); }

			private:
				void generate_impl(unsigned int n)
				{
					if (n == 0){
						m_results.push_back(m_track);
                        return;
					}
					
                    unsigned int k = 1;
					do
					{
						m_track.push(k);
						generate_impl(n - k);
						m_track.pop();
						k++;
                    }while (k <= n);
				}
			private:
				std::stack<unsigned int> m_track;
				std::list<std::stack<unsigned int>> m_results; 
		};
	}
}