def roundup(x):
    return 10*(x//10 + 1) if x%10 else x

class UnionFind:
    def __init__(self,n):
        self.numcars = 0
        self.sum = 0
        self.componentsize = [0]*n
        self.p = [-1]*n

    def addsingleton(self,x,size):
        self.numcars += 1
        self.sum += roundup(size)
        self.componentsize[x] = size
        self.p[x] = x

    def find(self,x):
        if self.p[x] == x:
            return x
        else:
            self.p[x] = self.find(self.p[x])
            return self.p[x]

    def union(self,a,b):
        A = self.find(a)
        B = self.find(b)
        # For this problem we can guarantee A != B

        self.sum -= roundup(self.componentsize[A]) + roundup(self.componentsize[B])
        self.componentsize[A] += self.componentsize[B]
        self.sum += roundup(self.componentsize[A])
        self.p[B] = A
        self.numcars -= 1

N = int(input().rstrip())

coaches = list(map(int, input().rstrip().split()))
timeline = list(map(int, input().rstrip().split()))[::-1]
uf = UnionFind(N)

best = 0
for x in timeline:
    x -= 1 # offset 1 index
    uf.addsingleton(x, coaches[x])
    if x > 0 and uf.p[x-1] != -1:
        uf.union(x, x-1)
    if x+1 < N and uf.p[x+1] != -1:
        uf.union(x, x+1)
    best = max(best, uf.numcars*uf.sum)

print(best)
