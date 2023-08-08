t = int(input())

for _ in range(t):
    in_str = input()
    m_val = int(in_str)

    in_arr = list(map(int, in_str))[::-1] + [0]

    k = 0
    for i in range(len(in_arr) - 1):
        if in_arr[i] == 10:
            in_arr[i] = 0
            in_arr[i + 1] += 1
            k = i + 1
        if in_arr[i] > 4:
            in_arr[i] = 0
            in_arr[i + 1] += 1
            k = i + 1
    in_arr = in_arr[k:][::-1] + [0 for _ in range(k)]
    m_val = max(m_val, int(''.join(map(str, in_arr))))
    print(m_val)
