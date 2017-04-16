#pragma once

namespace junk
{
	namespace array_rotation_point
	{
        template<typename T>
		int get_array_rotation_point(int *data, int l, int r, int len)
		{
			if (l > r){
				return 0;
			}
		
			int mid = l + (r - l) / 2;

			if (((mid - 1) < 0 ? data[len - 1] : data[mid - 1]) > data[mid] && 
				data[mid] < (mid + 1 == len ? data[0] : data[mid + 1])){
				return mid;
			}
			
			if (data[mid] < data[l]){ // pivot point on the left
				return get_array_rotation_point<T>(data, l, mid - 1, len);
			}
			return get_array_rotation_point<T>(data, mid + 1, r, len); // pivot on the right
		}
	}
}