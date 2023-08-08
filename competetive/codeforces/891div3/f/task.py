import math
from collections import defaultdict


t = int(input())

for _ in range(t):
    n = int(input())
    arr = list(map(int, input().split()))
    xmap = defaultdict(int)

    for a in arr:
        xmap[a] += 1
    
    q = int(input())
    for _ in range(q):
        x, y = map(int, input().split())

        delta = x**2 - 4 * y

        if delta < 0:
            print(0, end=' ')
            continue
        if delta == 0:
            x = x / 2
            print((xmap[x] * (xmap[x] - 1)) // 2, end=' ')
            continue

        x1 = (x - math.sqrt(delta)) / 2
        x2 = (x + math.sqrt(delta)) / 2

        if x1.is_integer() and x2.is_integer():
            x1 = int(x1)
            x2 = int(x2)

            if x1 == x2:
                print((xmap[x1] * (xmap[x1] - 1)) // 2, end=' ')
            else:
                print(xmap[x1] * xmap[x2], end=' ')
        else:
            print(0, end=' ')
    print()