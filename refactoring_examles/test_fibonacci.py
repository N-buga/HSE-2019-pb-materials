from fibonacci import fibonacci


def test_fibonacci():
    assert fibonacci(0) == []
    assert fibonacci(3) == [0, 1, 1]
