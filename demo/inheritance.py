#!/usr/bin/env python3
class MyBaseClass:
    VAL = 1

    def __init__(self):
        print('inited MyBaseClass')

    def foo(self):
        print('foo')

    def bar(self):
        self.foo()
        pass


class MyBaseClass2:
    def foo(self):
        print('Class2')


class MyDerivedClass(MyBaseClass, MyBaseClass2):
    def __init__(self):
        super().__init__()
        print('inited MyDerivedClass')

    def foo(self):
        print('foo2')
        print(type(super()))


x = MyDerivedClass()
x.foo()

print(isinstance(x, MyDerivedClass))
print(isinstance(x, MyBaseClass))
print(type(x) == MyDerivedClass)
print(type(x) == MyBaseClass)