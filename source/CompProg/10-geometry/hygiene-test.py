import random

print(str(10**5))

for i in range(0, 10**5):
    x = random.randint(0, 10**6)
    y = random.randint(0, 10**6)

    print(str(x) + " " + str(y))
