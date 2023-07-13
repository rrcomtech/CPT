import math

mod = 10**9 + 7
factorials = [1]


def extended_gcd(a, b):
    if b == 0:
        return a, 1, 0
    else:
        gcd, x, y = extended_gcd(b, a % b)
        return gcd, y, x - (a // b) * y


def modular_inverse(num):
    gcd, x, _ = extended_gcd(num, mod)
    if gcd == 1:
        return (x % mod + mod) % mod
    else:
        raise ValueError("Modular inverse does not exist")


def choose(n, k):
    upper_part = factorials[n + k - 1]

    lower_left = factorials[n - 1]
    lower_right = factorials[k]
    lower_part = (lower_left * lower_right) % mod

    inv = modular_inverse(lower_part)
    res = (upper_part * inv) % mod

    return res


def solve(l,h,n):
    rest_problems = n - 2

    if rest_problems == 0:
        print("1")
        return

    possibs = choose(h - l + 1, rest_problems)
    print(int(possibs))

largest_difference = 0

t = int(input())
cases = []
for i in range(0, t):
    l,h,n = [int(x) for x in input().split(" ")]
    largest_difference = max(largest_difference, (h - l + 1) + n)
    cases.append([l,h,n])

ans=1
for i in range(2,largest_difference + 1):
    factorials.append(ans)
    ans = (ans * i) % mod

for i in range(0, t):
    solve(cases[i][0], cases[i][1], cases[i][2])
