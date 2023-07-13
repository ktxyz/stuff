def sum_strings(x, y):
    if len(x) < len(y):
        x, y = y, x
    x, y = list(x[::-1]), list(y)
    r , i = 0, 0
    while y or r > 0:
        if i >= len(x):
            if r > 0:
                x.append('1')
            break
        if y:
            c = int(y.pop())
        else:
            c = 0
        x[i] = str(int(x[i]) + c + r)
        if len(x[i]) > 1:
            x[i] = x[i][1]
            r = 1
        i += 1
    return ''.join(reversed(x))

print(sum_strings('123', '456'))