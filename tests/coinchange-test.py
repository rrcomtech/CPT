intv = 50

for i in range(-intv, intv):
    for j in range(-intv, intv):
        for k in range(-intv, intv):
            if (1597 * i + 2584 * j + k == 2080):
                print(str(i) + "*1597 + " + str(j) + "*2584 + " + str(k) + " = 2080")