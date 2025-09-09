def two_sum(nums, target):
    frac_idx = {}
    for i, n in enumerate(nums):
        if target - n in frac_idx:
            return [fr]