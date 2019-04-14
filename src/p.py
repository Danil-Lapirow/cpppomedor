def fib(n):
    a = b = 1

    i = 3
    while i <= n:
        a, b = b, b + a
        i += 1

    return b


for i in range(1, 71):
    print(fib(i))
