import re

def expand(expr):
    expr = re.split(r"\(([-+]?\d*)?([a-zA-Z])([-+])?(\d+)\)\^(\d+)", expr)[1:-1]
    if expr[0] == "":
        expr[0] = "1"
    if expr[0] == "-":
        expr[0] = "-1"
    expr[0] = int(expr[0])
    expr[3] = int(expr[3])
    expr[4] = int(expr[4])
    if expr[4] == 0:
        return "1"
    elif expr[0] == 0 and expr[3] == 0:
        return "0"
    elif expr[0] == 0:
        return str(expr[3]**expr[4])
    elif expr[3] == 0:
        return str(expr[0]**expr[4]) + expr[1] + "^" + str(expr[4])
    
    res = ""
    coeff = 1
    for i in range(expr[4] + 1):
        pow_x = expr[4] - i
        pow_y = i

        x_coeff = coeff * expr[0]**pow_x * expr[3]**pow_y
        if abs(x_coeff) > 1:
            res += str(x_coeff)
        elif pow_x == 0:
            res += str(coeff * expr[3]**pow_y)
        
        if abs(x_coeff) == 1 and x_coeff < 0:
            res += "-"

        if pow_x > 0:
            res += expr[1]
        if pow_x > 1:
            res += "^" + str(pow_x)
        res += "-" if i % 2 == 0 and expr[2] != "+" else "+"
        coeff = coeff * (expr[4] - i)//(i + 1)

    if res[-1] == "+" or res[-1] == "-":
        res = res[:-1]

    if len(res) > 1:
        for i in range(len(res)-1):
            if len(res) <= i:
                break
            if res[i] == "+" and res[i+1] == "-":
                res = res[:i] + "-" + res[i+2:]
            elif res[i] == "-" and res[i+1] == "-":
                res = res[:i] + "+" + res[i+2:]
    return res
