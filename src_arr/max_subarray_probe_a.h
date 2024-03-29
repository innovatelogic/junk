#pragma once

#include <algorithm>
#include <limits.h>

namespace junk
{
	namespace max_subarray_probe_a
	{
        template<typename T>
		int max_cross(int *data, int start, int mid, int end)
		{
			// left side max sum [start, mid]
			int lmax = INT_MIN;
			int sum = 0;
			for (int i = mid; i >= start; i--)
			{
				sum += data[i];
				if (sum > lmax){
                    lmax = sum;
				}
			}
			
			// right side max sum [mid + 1, end]
			int rmax = INT_MIN;
			sum = 0;
			for (int i = mid + 1; i <= end; i++)
			{
				sum += data[i];
				if (sum > rmax){
					rmax = sum;
				}
			}
			return lmax + rmax;
		}
		
		/*!
			Returns max sum of sequence of subarray in array
			Ex. in { -2, -5, 6, -2, -3, 1, 5, -6 } 
			max sequence {6, -2, -3, 1, 5} 
			sum: 7
		*/
        template<typename T>
		int max_subarray(int *data, int start, int end)
		{
			if (start == end){
				return data[start];
			}
			
			int mid = (start + end) / 2;
			
			int left = max_subarray<T>(data, start, mid);
			int right = max_subarray<T>(data, mid + 1, end);
			int cross = max_cross<T>(data, start, mid, end);
			
			return std::max(left, std::max(right, cross));
		}
	}
}