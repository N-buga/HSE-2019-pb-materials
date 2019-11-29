import pytest
import sys


def test_stub_once(mocker):
    def foo(on_something):
        on_something('foo', 'bar')

    stub = mocker.stub(name='on_something_stub')

    foo(stub)
    stub.assert_called_once_with('foo', 'bar')


def on_something(value, value2):
    pass


def test_stub_multiple(mocker):
    def foo(on_something):
        on_something('foo', value='bar')

    stub = mocker.stub(name='on_something_stub')

    foo(stub)
    foo(stub)
    foo(stub)

    assert len(stub.call_args_list) == 3
    for args, kwargs in stub.call_args_list:
        assert args == ('foo',)
        assert kwargs == {'value': 'bar'}


if __name__ == "__main__":
    pytest.main(sys.argv)
