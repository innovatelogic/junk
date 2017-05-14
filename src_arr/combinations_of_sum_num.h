
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
			/*!
				List all combination sums on N 
				Ex. 4 -> {1, 1, 1, 1},
						 {1, 1, 2},
						 {1, 2, 1},
						 {1, 3},
						 {2, 1, 1},
						 {2, 2},
						 {3, 1},
						 {4}
			*/
				void generate_impl(unsigned int n)
				{
					// base case
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