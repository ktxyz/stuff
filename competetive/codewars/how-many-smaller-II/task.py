class FenwickTree:
    def __init__(self, n):
        self.n = n
        self.tree = [0] * (n + 1)

    def add(self, x, val):
        x += 1
        while x <= self.n:
            self.tree[x] += val
            x += x & -x
    
    def _sum(self, x):
        x += 1
        ans = 0
        while x > 0:
            ans += self.tree[x]
            x -= x & -x
        return ans

    def sum(self, l, r):
        return self._sum(r) - self._sum(l - 1)

def smaller(arr):
    arr = arr[::-1]
    mapping = {}
    for i, v in enumerate(list(sorted(set(arr)))):
        mapping[v] = i
    tree = FenwickTree(len(mapping))
    ans = []
    for v in arr:
        tree.add(mapping[v], 1)
        ans.append(tree.sum(0, mapping[v] - 1))
    return ans[::-1]
