


# Given an unsorted array of integers, find the length of the longest consecutive elements sequence.
# For example, given [100, 4, 200, 1, 3, 2], the longest consecutive elements sequence should be [1, 2, 3, 4]. Its length is 4.
# Your algorithm should run in O(n) complexity.
# @param nums, a list of integers


#  Example: 
#  [100, 4, 200, 1, 3, 2, 101]
#  Break down for example to continous sequences: 
#  [1, 2, 3, 4]
#  [100, 101] 
#  [200]

#  For each element in sequence
#  check previous element (n - 1) is in the set
#  [1, 2, 3, 4]  
#      ^
#      Start processing if current element is the START of the sequence [1, 2, ...]   

def longest_consequtive_sequence(nums):
    if not nums:
        return 0
    nums = set(nums)
    max_len = 1
    for n in nums:
        if n - 1 in nums:
            curr_len = 2
            curr_n = n
            while curr_n + 1 in nums:
                curr_len += 1
                curr_n += 1
            max_len = max(max_len, curr_len)
    return max_len
