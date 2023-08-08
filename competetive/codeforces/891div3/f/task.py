import math
from collections import Counter


t = int(input())

for _ in range(t):
    n = int(input())
    arr = [*map(int, input().split())]
    xmap = Counter(map(str, arr))

    for a in arr:
        if a in xmap:
            xmap[a] += 1
        else:
            xmap[a] = 0
    
    q = int(input())
    for _ in range(q):
        x, y = map(int, input().split())

        delta = x * x - 4 * y

        if delta < 0:
            print(0)
            continue

        delta_sqrt = int(math.sqrt(delta))
        x1 = (x - delta_sqrt) // 2
        x2 = (x + delta_sqrt) // 2

        if (x1 + x2 != x) or (x1 * x2 != y):
            print(0)
        else:
            x1 = str(x1)
            x2 = str(x2)
            if x1 == x2:
                print((xmap[x1] * (xmap[x1] - 1)) // 2)
            else:
                print(xmap[x1] * xmap[x2])