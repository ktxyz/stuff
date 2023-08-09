t = int(input())

for _ in range(t):
    b, c, h = map(int, input().split())
    height = max(0, min(b - 1, c + h))

    if height > 0:
        print(2 * height + 1)
    else:
        print(0)