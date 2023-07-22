import bisect

class SortedList:
    def __init__(self):
        self.list = []

    def insert(self, value):
        bisect.insort(self.list, value)

    def remove(self, value):
        index = self.list.index(value)
        del self.list[index]

    def __getitem__(self, index):
        return self.list[index]

    def __len__(self):
        return len(self.list)

def calculate(rectangles):
    events = []
    for x0, y0, x1, y1 in rectangles:
        events.append((y0, 1, x0, x1)) # Start event
        events.append((y1, -1, x0, x1)) # End event
    events.sort()
    x_coords = SortedList()
    active_width = 0
    last_y = 0
    area = 0
    for y, type, x0, x1 in events:
        if len(x_coords) > 0:
            area += (y - last_y) * active_width
        last_y = y
        if type == 1:
            x_coords.insert((x0, x1))
        else:
            try:
                x_coords.remove((x0, x1))
            except ValueError:
                pass
        active_width = 0
        if len(x_coords) > 0:
            x_left, x_right = x_coords[0]
            for x0, x1 in x_coords:
                if x0 > x_right:
                    active_width += x_right - x_left
                    x_left = x0
                x_right = max(x_right, x1)
            active_width += x_right - x_left
    return area