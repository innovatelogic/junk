

# Example:
# [1, 3], [2, 6], [8, 10], [15, 18]
# [1, 6], [8, 10], [15, 18]
#
# sorted intervals:
# [1, 3] <- 
# [2, 6] <- 
# [5, 6]          
# [8, 10]
# [15, 18]

def merge_intervals(intervals):
    if not intervals:
        return []

    intervals.sort(key = lambda x: x[0])

    merged = [intervals[0]]
    for i in range(1, len(intervals)):
        if intervals[i][0] <= merged[-1][1]:
            merged[-1][1] = max(merged[-1][1], intervals[i][1])
        else:
            merged.append(intervals[i])

    return merged

def test_merge_intervals():
    assert merge_intervals([]) == []
    assert merge_intervals([[1, 3], [2, 6], [8, 10], [15, 18]]) == [[1, 6], [8, 10], [15, 18]]
    assert merge_intervals([[1, 4], [4, 5]]) == [[1, 5]]
    assert merge_intervals([[1, 4], [2, 3]]) == [[1, 4]]
    assert merge_intervals([[1, 4], [0, 4]]) == [[0, 4]]
    assert merge_intervals([[1, 4], [0, 1]]) == [[0, 4]]
    assert merge_intervals([[1, 4], [0, 0]]) == [[0, 0], [1, 4]]
    assert merge_intervals([[1, 4], [0, 0], [5, 6]]) == [[0, 0], [1, 4], [5, 6]]
    assert merge_intervals([[1, 4], [0, 0], [5, 6], [4, 5]]) == [[0, 0], [1, 6]]