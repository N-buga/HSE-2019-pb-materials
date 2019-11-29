import pytest
import sys
import pytest_mock
from io import StringIO


class MyClass:
    VAL = 1

    def __init__(self, val):
        self.val = val

    def add(self, other_value):
        return self.val + other_value


def read_number():
    return int(input())


def test_read_number(mocker: pytest_mock.MockFixture):
    mocker.patch.object(sys, 'stdin', StringIO('12'))
    assert read_number() == 12


def test_MyClass(mocker):
    my_class = MyClass(1)
    mocker.patch.object(my_class, 'add', return_value=10)
    assert my_class.add(1) == 10

    mocker.patch.object(my_class, 'add', lambda val: val + 10)
    assert my_class.add(1) == 11


if __name__ == "__main__":
    pytest.main(sys.argv)