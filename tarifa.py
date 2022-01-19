X = int(input().rstrip())
N = int(input().rstrip())

carryover = 0
for _ in range(N):
    carryover = carryover + X - int(input().rstrip())

print(carryover + X)
