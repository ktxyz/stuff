def solve(k, arr_const):
    if k == 1:
        return [i + 1 for i in range(len(arr_const))]
    arr = arr_const.copy()
    arr = [(a % k, i) for i, a in enumerate(arr)]
    arr.sort(key=lambda x: (-x[0] if x[0] > 0 else -100000000000, x[1]))
    return [a[1] + 1 for a in arr]

t = int(input())
for _ in range(t):
    _, k = map(int, input().split())
    arr = list(map(int, input().split()))
    print(*solve(k, arr))