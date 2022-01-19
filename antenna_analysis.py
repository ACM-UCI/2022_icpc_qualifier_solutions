from math import inf

N,C = map(int, input().rstrip().split())
arr = list(map(int, input().rstrip().split()))
ans = [0] * N

minimum = inf
maximum = -inf
for i,v in enumerate(arr):
    minimum = min(minimum, v)
    maximum = max(maximum, v)
    ans[i] = max(abs(v-minimum), abs(maximum-v))
    minimum += C
    maximum -= C

print(' '.join(map(str,ans)))
