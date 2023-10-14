from functools import lru_cache

MOD = 998244353

@lru_cache(maxsize=None)
def fast_pow_mod(a, b, m):
    if b == 0:
        return 1
    if b == 1:
        return a % m
    val = fast_pow_mod(a, b // 2, m) % m
    if b % 2 == 0:
        return (val * val) % m
    return (((val * val) % m) * a) % m

def height(n, m):
    if n == 0 or m == 0:
        return 0
    if n >= m:
        return (2**m - 1) % MOD
    s = 0
    m = m % MOD
    b = 1
    for i in range(1, n + 1):
        b = (b * (m - i + 1) * fast_pow_mod(i, MOD - 2, MOD)) % MOD
        s = (s + b) % MOD
    return s % MOD