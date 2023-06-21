def myster_rec(level, idx):
    if level == 1:
        return ['0', '1'][idx]
    
    middle = 2 ** (level - 1)
    if idx < middle:
        return '0' + myster_rec(level - 1, idx)
    else:
        return '1' + myster_rec(level - 1, middle - 1 - (idx - middle))

def mystery(n):
    return int(myster_rec(len(bin(n)[2:]), n), 2)

def mystery_inv_rec(level, value):
    if level == 1:
        return 0 if value[0] == '0' else 1
    val = mystery_inv_rec(level - 1, value[1:])
    if value[0] == '1':
        val = 2 ** level - val - 1
    return val

def mystery_inv(n):
    return mystery_inv_rec(len(bin(n)[2:]), bin(n)[2:])

def name_of_mystery():
    return 'Gray code'

