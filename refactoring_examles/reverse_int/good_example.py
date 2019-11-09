#!/usr/bin/env python3
# 'Reverse integer'


def reverse_int(x: int) -> int:
    digits = str(x)
    need_str = "".join(reversed(digits))  # list() can be omitted sometimes
    return int(need_str)


if __name__ == '__main__':
    x = 1234567890123
    print(reverse_int(x))
