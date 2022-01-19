X = int(input().rstrip())
N = int(input().rstrip())
print((N+1)*X - sum(int(input().rstrip()) for _ in range(N)))
