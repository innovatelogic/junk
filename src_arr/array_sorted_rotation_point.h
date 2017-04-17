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

        template<typename T>
        int binary_search(int *data, int l, int r, int x)
        {
            if (l <= r)
            {
                int mid = (l + r) / 2;

                if (data[mid] == x) {
                    return mid;
                }

                if (x < data[mid]) {
                    return binary_search<T>(data, l, mid - 1, x);
                }
                return binary_search<T>(data, mid + 1, r, x);
            }
            return -1;
        }

        template<typename T>
        int binary_search_rotated(int *data, int len, int x)
        {
            int rev_point = get_array_rotation_point<T>(data, 0, len - 1, len);

            int left = 0;
            int right = len - 1;

            if (rev_point > 0)
            {
                if (x >= data[0] && x <= data[rev_point - 1]) { // search on the left
                    right = rev_point - 1;
                }
                else {
                    left = rev_point;
                }
            }

            return binary_search<T>(data, left, right, x);
        }
	}
}