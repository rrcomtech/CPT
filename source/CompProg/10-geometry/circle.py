import math


def solve(x1, y1, r1, x2, y2, r2):
    d = math.sqrt((x2 - x1)**2 + (y2 - y1)**2)
    d = round(d,2)

    if d > r1 + r2:
        print("0")
        return

    if d < abs(r1 - r2):
        print("0")
        return

    if d == 0 and r1 == r2:
        print("oo")
        return

    if d == r1 + r2:
        print("1")
        return

    if d < r1 + r2:
        print("2")
        return

    return


t = int(input())

for _ in range(0, t):
    x1,y1,r1 = [abs(int(x)) for x in input().split(" ")]
    x2,y2,r2 = [abs(int(x)) for x in input().split(" ")]
    solve(x1, y1, r1, x2, y2, r2)