def mat_mult(mat1, mat2, mod):
    n = len(mat1)
    m = len(mat2[0])
    l = len(mat2)
    answer = [[0] * m for _ in range(n)]
    for i in range(n):
        for j in range(m):
            for k in range(l):
                answer[i][j] = (answer[i][j] + mat1[i][k] * mat2[k][j]) % mod
    return answer

def mat_exp_fast(mat, n, mod):
    if n == 1:
        return mat
    val = mat_exp_fast(mat_mult(mat, mat, mod), n // 2, mod)
    if n & 1:
        val = mat_mult(mat, val, mod)
    return val

def ways(n, k):
    if n == 1:
        return k
    if n == 2:
        return k * k
    if k == 1:
        return 0 if n > 2 else 1
    
    same, diff = k, k * (k - 1)
    trans = [[0, 1], [k - 1, k - 1]]
    answer = mat_exp_fast(trans, n - 2, 10**9 + 7)

    return (answer[1][0] * same + answer[1][1] * diff + answer[0][0] * same + answer[0][1] * diff) % (10**9 + 7)


print("n=3, k=2, expected=6, got=", ways(3, 2))
print("n=4, k=5, expected=580, got=", ways(4, 5))
print("n=8638433, k=9944756, expected=895647343, got=", ways(8638433, 9944756))