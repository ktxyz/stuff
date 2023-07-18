import math

def prime_factors(n):
    factors = set()
    while n % 2 == 0:
        factors.add(2),
        n = n // 2
    for i in range(3, int(math.sqrt(n))+1, 2):
        while n % i== 0:
            factors.add(i)
            n = n // i
    if n > 2:
        factors.add(n)
    return factors

def euler_totient_fast(n):
    if n == 1:
        return 1
    else:
        factors = prime_factors(n)
        totient = n
        for p in factors:
            totient *= (1 - 1 / p)
        return int(totient)

def tower(base, height, modulus):
    if modulus == 1:
        return 0
    if base == 1 or height == 0:
        return 1
    if height == 1:
        return base % modulus
    if height == 2:
        return pow(base, base, modulus)

    phi_modulus = euler_totient_fast(modulus)
    power = tower(base, height - 1, phi_modulus)
    
    if height > 2 and power == 0:
        power += phi_modulus

    return pow(base, power, modulus)
