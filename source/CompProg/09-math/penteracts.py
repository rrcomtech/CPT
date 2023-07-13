from math import log, exp

def even_a(n, b):
    a_pow5 = n + pow(b, 5)

    a = 0
    if (a_pow5 < 0):
        a = exp(log(-a_pow5)/5)
        a = -a
    else:
        a = exp(log(a_pow5)/5)

    # Round on a number of decimals
    a = round(a, 5)

    if a.is_integer():
        print(int(a), int(b), sep=" ")
        return True

    return False

def solve(n):
    max = 1_000_000

    if not even_a(n, 0):
        for dist in range(1, max):
            if even_a(n, dist):
                return
            if even_a(n, -dist):
                return

n = int(input())
solve(n)