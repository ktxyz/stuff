import math
import time

masks = [0] * 10
last_computed_mask = 0

def compute_mask(new_computed_mask):
    global masks
    global last_computed_mask
    for i in range(last_computed_mask, new_computed_mask):
        k = i
        while k > 0:
            c = k % 10
            masks[c] |= 1 << i
            k = k // 10
    last_computed_mask = new_computed_mask

memory = {}
memory_vals = {}
def find_num(n):
    return solve(n, False)

boundary = int(math.sqrt(18000))

def solve(n, force=False):
    global masks
    global memory
    global memory_vals
    if n < 11:
        return n
    
    if n in memory.keys():
        return memory[n]
    
    if not force and n > boundary and boundary < 18001:
        solve(18000, True)
        return memory[n]

    if len(memory_vals.keys()) > 0:
        m_last_val = max(x for x in memory_vals.keys() if x <= n)
        seq, x = memory_vals[m_last_val]
    else:
        m_last_val = 0
        seq, x = 1, 0
    
    compute_mask(int(n * (math.log2(n) - 1)))
    
    for j in range(n - m_last_val):
        memory_vals[j + m_last_val] = (seq, x)
        memory[j + m_last_val] = x.bit_length() - 1
        M = seq
        for m in masks:
            if x & m:
                M |= m
        x = ~M & (M+1)
        seq |= x
    memory[n] = x.bit_length() - 1
    return x.bit_length() - 1

time_start = time.time()
print(find_num(17999))
print(time.time() - time_start)

time_start = time.time()
print(find_num(18000))
print(time.time() - time_start)