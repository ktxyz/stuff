class Node:
    def __init__(self, start, end):
        self.start = start
        self.end = end
        self.total = 0
        self.count = 0
        self.left = None
        self.right = None

    def _split(self):
        mid = (self.start + self.end) // 2
        self.left = Node(self.start, mid)
        self.right = Node(mid+1, self.end)

class SegmentTree:
    def __init__(self, start, end):
        self.root = Node(start, end)

    def _init_tree(self, start, end):
        if start > end:
            return None
        node = Node(start, end)
        if start == end:
            return node
        mid = (start + end) // 2
        node.left = self._init_tree(start, mid)
        node.right = self._init_tree(mid + 1, end)
        return node

    def update(self, start, end, value):
        self._update(self.root, start, end, value)

    def _update(self, node, start, end, value):
        if node.left is None:
            node._split()

        if start <= node.start and node.end <= end:
            node.count += value
        else:
            mid = (node.start + node.end) // 2
            if start <= mid:
                self._update(node.left, start, min(end, mid), value)
            if mid < end:
                self._update(node.right, max(start, mid+1), end, value)

        if node.count > 0:
            node.total = node.end - node.start + 1
        else:
            node.total = (node.left.total if node.left else 0) + (node.right.total if node.right else 0)

    def total(self):
        return self.root.total

def calculate(rectangles):
    if not rectangles:
        return 0

    events = []
    for x0, y0, x1, y1 in rectangles:
        events.append((y0, 1, x0, x1-1))
        events.append((y1, -1, x0, x1-1))
    events.sort()

    min_x = min(event[2] for event in events)
    max_x = max(event[3] for event in events)

    tree = SegmentTree(min_x, max_x) 
    active_width = 0
    last_y = 0
    area = 0

    for y, type, x0, x1 in events:
        if y > last_y:
            area += (y - last_y) * active_width
        last_y = y
        tree.update(x0, x1, type)
        active_width = tree.total()

    return area

# Testing
test_cases = [
    ("0 rectangles", 0, []),
    ("1 rectangle", 1, [(0,0,1,1)]),
    ("1 rectangle (version 2)", 22, [(0, 4, 11, 6)]),
    ("2 rectangles", 2, [(0,0,1,1), (1,1,2,2)]),
    ("2 rectangle (version 2)", 4, [(0,0,1,1), (0,0,2,2)]),
    ("3 rectangle ", 36, [(3,3,8,5), (6,3,8,9),(11,6,14,12)]),
]

for name, expected, rectangles in test_cases:
    result = calculate(rectangles)
    assert result == expected, f"For test case {name}, expected {expected} but got {result}"
print("All test cases passed!")
