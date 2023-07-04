from enum import Enum
import re


class Type(Enum):
    VAL = 1
    OP = 2
    L_PARENT = 3
    R_PARENT = 4
    NEG = 5

class Token:
    def __init__(self, type, value):
        self.type = type
        self.value = value
    def __str__(self) -> str:
        return f'{self.type}: {self.value}'
    def __repr__(self) -> str:
        return self.__str__()

def tokenize(expression):
    regex_res = re.findall(r'\(|\)|[\-\+\*\/]|[0-9]+\.?[0-9]*', expression)

    tokens = []
    last_tt = None
    for t in regex_res:
        if t == '-':
            if last_tt == Type.OP or last_tt is None or last_tt == Type.L_PARENT:
                tokens.append(Token(Type.NEG, t))
            else:
                tokens.append(Token(Type.OP, t))
        elif t == '+' or t == '*' or t == '/':
            tokens.append(Token(Type.OP, t))
        elif t == '(':
            tokens.append(Token(Type.L_PARENT, t))
        elif t == ')':
            tokens.append(Token(Type.R_PARENT, t))
        else:
            tokens.append(Token(Type.VAL, t))
        last_tt = tokens[-1].type
    
    no_neg = []
    balance = 0
    neg_balance = 0
    tokens = tokens[::-1]
    while len(tokens) > 0:
        token = tokens.pop()
        if token.type == Type.NEG:
            if tokens[-1].type == Type.VAL:
                val = tokens.pop()
                no_neg.append(Token(Type.VAL, -float(val.value)))
                continue
            else:
                no_neg.append(Token(Type.L_PARENT, '('))
                no_neg.append(Token(Type.VAL, '-1'))
                no_neg.append(Token(Type.OP, '*'))
                neg_balance += 1
                balance += 1
            continue
        no_neg.append(token)
        if balance > 0:
            if token.type == Type.L_PARENT:
                balance += 1
            elif token.type == Type.R_PARENT:
                balance -= 1
            if balance > 0 and balance <= neg_balance:
                while neg_balance > 0:
                    no_neg.append(Token(Type.R_PARENT, ')'))
                    neg_balance -= 1
                    balance -= 1
    no_neg = [Token(Type.L_PARENT, '(')] + no_neg + [Token(Type.R_PARENT, ')')]
    return no_neg[::-1]

def getNextValHigh(tokens):
    token = tokens.pop()
    if token.type == Type.VAL:
        return float(token.value)
    elif token.type == Type.L_PARENT:
        return evalE(tokens)

def getNextValLow(tokens):
    token = tokens.pop()
    if token.type == Type.VAL:
        val = float(token.value)
    elif token.type == Type.L_PARENT:
        val = evalE(tokens)
    while len(tokens) > 0 and tokens[-1].type == Type.OP and tokens[-1].value in ['*', '/']:
        op = tokens.pop()
        r_val = getNextValHigh(tokens)
        if op.value == '*':
            val *= r_val
        elif op.value == '/':
            val /= r_val
    return val

def evalE(tokens):
    val = getNextValLow(tokens)
    while len(tokens) > 0:
        op = tokens.pop()
        if op.value == '+':
            r_val = getNextValLow(tokens)
            val = val + r_val
        elif op.value == '-':
            r_val = getNextValLow(tokens)
            val = val - r_val
        elif op.value == '*':
            r_val = getNextValHigh(tokens)
            val = val * r_val
        elif op.value == '/':
            r_val = getNextValHigh(tokens)
            val = val / r_val
        elif op.value == ')':
            return val
    return val

def calc(expression):
    tokens = tokenize(expression)
    return evalE(tokens)