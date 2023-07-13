def last_digit(lst):
    if not lst:
        return 1
    last = 1
    for x in reversed(lst):
        last = x ** (last if last < 4 else last % 4 + 4)
    return last % 10