#!/usr/bin/env python
import pytest
import pytest_mock
import sys
from io import StringIO


class MyClass:
    DEFAULT = 10

    def __init__(self, val: int):
        self.val = val

    def add(self, another_val) -> int:
        return self.val + another_val

    def add_to_default(self) -> int:
        return self.val + self.DEFAULT

    def do_nothing(self, int_value):
        return int_value


def read_number():
    return int(input())


def test_read_number(mocker: pytest_mock.MockFixture):
    mocker.patch.object(sys, 'stdin', StringIO('12'))
    assert read_number() == 12


def test_my_class_func(mocker: pytest_mock.MockFixture):
    mocker.patch.object(MyClass, 'DEFAULT', 1000)
    my_class = MyClass(1)
    mocker.patch.object(my_class, 'val', 1234)
    mocker.patch.object(my_class, 'add', lambda other_val: other_val)
    assert my_class.val == 1234
    assert my_class.add(5) == 5
    assert my_class.add_to_default() == 2234

    # mocker.patch.object(my_class, 'do_nothing', return_value='1234')
    # assert my_class.do_nothing() == '1234'


if __name__ == "__main__":
    pytest.main(sys.argv)