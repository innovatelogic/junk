#pragma once

#include <stack>

namespace junk
{
	namespace histogram_max_rect_probe_a
	{
		/*!              
		                
		              * 
		          * * *   *
		        * * * * * *
				- - - - - -
				0 1 2 3 4 5         
		*/
        template<typename T>
		int backtrack_area(std::stack<T> &s, T *hist, int i)
		{
			T area = 0;
			
			T top = s.top();
			s.pop();
			if (s.empty()){
				area = hist[top] * i;
			}
			else{
				area = hist[top] * (i - s.top() - 1);
			}
			return area;
		}
		
        template<typename T>
        T get_max_rect(T *hist, int n)
		{
			if (!hist){
				return 0;
			}
			
			T max_area = 0;
			std::stack<T> s;
			
			int i = 0;
			while (i < n)
			{
				if (s.empty() || hist[s.top()] <= hist[i]){
					s.push(i++);
				}
				else
				{
					T area = backtrack_area<T>(s, hist, i);
					if (area > max_area){
						max_area = area;
					}
				}
			}
			
			while (!s.empty())
			{
				T area = backtrack_area<T>(s, hist, i);
				if (area > max_area){
					max_area = area;
				}
			}
			return max_area;
		}
	}
}