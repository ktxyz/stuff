def solve(values, operators):
    n = len(values)

    true = [[0 for _ in range(n)] for _ in range(n)]
    false = [[0 for _ in range(n)] for _ in range(n)]

    for i in range(n):
        if values[i] == 't':
            true[i][i] = 1
            false[i][i] = 0
        else:
            true[i][i] = 0
            false[i][i] = 1

    for length in range(1, n):
        for start in range(n - length):
            end = start + length
            for k in range(start, end):
                total = ((true[start][k] + false[start][k]) * (true[k+1][end] + false[k+1][end]))

                if operators[k] == '&':
                    true_count = true[start][k] * true[k+1][end]
                    false_count = total - true_count
                    true[start][end] = (true[start][end] + true_count)
                    false[start][end] = (false[start][end] + false_count)
                elif operators[k] == '|':
                    false_count = false[start][k] * false[k+1][end]
                    true_count = total - false_count
                    true[start][end] = (true[start][end] + true_count)
                    false[start][end] = (false[start][end] + false_count)
                elif operators[k] == '^':
                    true_count = true[start][k] * false[k+1][end] + false[start][k] * true[k+1][end]
                    false_count = true[start][k] * true[k+1][end] + false[start][k] * false[k+1][end]
                    true[start][end] = (true[start][end] + true_count)
                    false[start][end] = (false[start][end] + false_count)

    return true[0][n-1]
