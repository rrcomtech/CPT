MOD = 10**9 + 7

def calculate_distinct_contests(l, h, n):
    distinct_ratings = h - l + 1
    total_contests = pow(distinct_ratings, n, MOD)
    same_rating_contests = pow(distinct_ratings - 1, n, MOD)
    distinct_contests = (total_contests - same_rating_contests) % MOD
    return distinct_contests

# Read the number of test cases
t = int(input())

# Process each test case
for _ in range(t):
    l, h, n = map(int, input().split())
    result = calculate_distinct_contests(l, h, n)
    print(result)