import sys

def find_infinite_money_glitch(n, exchange_rates):
    # Step 1: Initialize variables
    dist = [float('inf')] * n
    dist[0] = 0
    parent = [-1] * n
    glitch_currencies = []

    # Step 2: Bellman-Ford algorithm
    for _ in range(n-1):
        for u in range(n):
            for v in range(n):
                if dist[u] + exchange_rates[u][v] < dist[v]:
                    dist[v] = dist[u] + exchange_rates[u][v]
                    parent[v] = u

    # Step 3: Check for negative cycles
    for u in range(n):
        for v in range(n):
            if dist[u] + exchange_rates[u][v] < dist[v]:
                # Negative cycle found
                # Step 4: Trace back the cycle
                cycle_start = v
                while cycle_start not in glitch_currencies:
                    glitch_currencies.append(cycle_start)
                    cycle_start = parent[cycle_start]

                glitch_currencies.append(cycle_start)
                return glitch_currencies[::-1]

    return None

# Step 0: Read input
n = int(input())
currencies = input().split()

exchange_rates = []
for _ in range(n):
    row = list(map(float, input().split()))
    exchange_rates.append(row)

# Step 5: Find infinite money glitch
glitch = find_infinite_money_glitch(n, currencies, exchange_rates)

# Step 6: Print the output
if glitch is None:
    print("noglitch")
else:
    print("money!")
    print(len(glitch))
    print(" ".join(currencies[i] for i in glitch))