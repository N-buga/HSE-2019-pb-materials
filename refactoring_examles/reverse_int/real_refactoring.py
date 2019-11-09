def reverse_integer(x):
    digits = []
    while x > 0:
        digits.append(x % 10)
        x //= 10
    n = len(digits)
    for i in range(n // 2):
        tmp = digits[n - i - 1]
        digits[n - i - 1] = digits[i]
        digits[i] = tmp

    for i in range(n):
        ten = 1
        for j in range(i):
            ten *= 10
        x += ten * digits[i]
    print(x)


if __name__ == '__main__':
    x = 1234567890123
    print(int("".join(reversed(str(x)))))
