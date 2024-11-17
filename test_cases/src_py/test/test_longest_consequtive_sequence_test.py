from .. import longest_consequtive_sequence as lcs

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

def test_longest_consequtive_sequence():
    assert longest_consequtive_sequence([]) == 0
    assert longest_consequtive_sequence([100, 4, 200, 1, 3, 2]) == 4
    assert longest_consequtive_sequence([100, 4, 200, 1, 3, 2, 101]) == 4
    assert longest_consequtive_sequence([0, 1, -1]) == 3