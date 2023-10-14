from functools import lru_cache

def balanced_parens(n):
    # Your code here!
    
    @lru_cache(maxsize=None)
    def _balance(prev, sum, left):
        if (sum > left):
            return []
        if left == 0 and sum != 0:
            return []
        if left == 0:
            return [prev]
        if sum < 0:
            return []
        ans = []
        l_par = prev + '('
        for p in _balance(l_par, sum + 1, left - 1):
            ans += [p]
        r_par = prev + ')'
        for p in _balance(r_par, sum - 1, left - 1):
            ans += [p]
        return ans
        
    return _balance('', 0, 2 * n)