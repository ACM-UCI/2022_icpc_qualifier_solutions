from math import inf, hypot

N = int(input().rstrip())
L,W = map(int, input().rstrip().split())
arr = sorted(int(input().rstrip()) for _ in range(N))
sep = L/(N//2-1)

dp = [[inf for __ in range(N+1)] for _ in range(N+1)]
dp[0][0] = 0

for r in range(N):
    for c in range(N):
        if r+c < N:
            dp[r+1][c] = min(dp[r+1][c], dp[r][c] + abs(arr[r+c] - r*sep))
            dp[r][c+1] = min(dp[r][c+1], dp[r][c] + hypot(arr[r+c] - c*sep, W))

print(dp[N//2][N//2])

