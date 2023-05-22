def min_palindrome_insertions(word):
    n = len(word)
    dp = [[0] * (n+1) for _ in range(n+1)]

    for i in range(n):
        dp[i][i] = 0

    for l in range(2, n+1):
        for i in range(n-l+1):
            j = i + l - 1
            if word[i] == word[j]:
                dp[i][j] = dp[i+1][j-1]
            else:
                dp[i][j] = min(dp[i+1][j] + 1, dp[i][j-1] + 1, dp[i+1][j-1] + 1)

    return dp[0][n-1]

print(min_palindrome_insertions("abc"))
