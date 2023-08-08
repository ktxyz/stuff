t = int(input())

for _ in range(t):
    n = int(input())
    a = list(map(int, input().split()))
    b = list(map(int, input().split()))

    diffs = [(a[i] - b[i], i + 1) for i in range(n)]
    diffs.sort(reverse=True)
    largest_diff = diffs[0][0]
    
    count = sum(1 for diff, _ in diffs if diff == largest_diff)
    
    strong = sorted([index for diff, index in diffs if diff == largest_diff])
    
    print(count)
    print(' '.join(map(str, strong)))
