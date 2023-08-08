t = int(input())

for i in range(t):
    n = int(input())
    arr = list(map(int, input().split()))

    odd_count = sum(1 for x in arr if x % 2 == 1)
    if odd_count % 2 == 0:
        print("YES")
    else:
        print("NO")