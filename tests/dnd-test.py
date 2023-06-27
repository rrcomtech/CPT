import random

print("2000")
for i in range(0, 2000):
    print(str(i) + " " + str(i + 1))

print("2000")
for i in range(0, 2000):
    print(str(i) + " " + str(i + 1))

print("100000")
for i in range(0, 100000):
    r1 = random.randint(1, 2000)
    r2 = random.randint(1, 2000)

    print(str(r1) + " " + str(r2))