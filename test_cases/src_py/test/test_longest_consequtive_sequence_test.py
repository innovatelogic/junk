from .. import longest_consequtive_sequence as lcs

def test_longest_consequtive_sequence():
    assert lcs.longest_consequtive_sequence([]) == 0
    assert lcs.longest_consequtive_sequence([100, 4, 200, 1, 3, 2]) == 4
    assert lcs.longest_consequtive_sequence([100, 4, 200, 1, 3, 2, 101]) == 4
    assert lcs.longest_consequtive_sequence([0, 1, -1]) == 3