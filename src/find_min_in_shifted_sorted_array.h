namespace junk
{
    // finds min element in shifted array where all elements are distinct 
    template<class T>
    T find_min_in_shifted_sorted_array(const T *arr, int left, int right)
    {
        if (left > right) { // case if array is already sorted
            return arr[0];
        }

        if (left == right) { // degrade range to one element case
            return arr[left];
        }

        const int mid = (left + right) / 2;

        // check frame [mid-1; mid; mid + 1]
        // [ mid-1; mid;|
        const int mid_left = mid - 1;
        if (mid_left >= 0 && arr[mid_left] > arr[mid]){
            return arr[mid];
        }

        // |mid; mid + 1]
        const int mid_right = mid + 1;
        if (mid_right <= right && arr[mid] > arr[mid_right]) {
            return arr[mid_right];
        }

        if (arr[right] < arr[mid]){
            return find_min_in_shifted_sorted_array(arr, mid + 1, right);
        }
        return find_min_in_shifted_sorted_array(arr, left, mid - 1);
    }

}