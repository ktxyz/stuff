M = 998244353
t = int(input())

rep = [0] * 1000001
sz = [0] * 1000001

def find(x):
    if rep[x] == x:
        return x
    rep[x] = find(rep[x])
    return rep[x]

def union(x, y):
    x = find(x)
    y = find(y)
    if x == y:
        return
    if sz[x] < sz[y]:
        x, y = y, x
    rep[y] = x
    sz[x] += sz[y]

def pow_fast(a, b, mod):
    if b == 0:
        return 1
    if b == 1:
        return a % mod
    v = pow_fast(a, b // 2, mod)
    v = (v * v) % mod
    if b % 2 == 1:
        v = (v * a) % mod
    return v

for _ in range(t):
    n, S = map(int, input().split())

    for i in range(1, n + 1):
        rep[i] = i
        sz[i] = 1

    edges = []
    for _ in range(n - 1):
        u, v, w = map(int, input().split())
        edges.append((w, u, v))
    edges.sort()

    ans = 1
    for e in edges:
        szu = sz[find(e[1])]
        szv = sz[find(e[2])]
        ans = (ans * pow_fast(S - e[0] + 1, szu * szv - 1, M)) % M
        union(e[1], e[2])
    
    print(ans)