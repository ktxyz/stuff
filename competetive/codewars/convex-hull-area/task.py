from math import dist
from functools import cmp_to_key as argcomp2


class Point:
    def __init__(self, x, y):
        self.x = x
        self.y = y
    
    def __eq__(self, other):
        return self.x == other.x and self.y == other.y
    
    def __lt__(self, other):
        if self.x == other.x:
            return self.y < other.y
        return self.x < other.x
    
    def __iter__(self):
        yield self.x
        yield self.y

    def swap(self):
        return Point(self.y, self.x)

def crossProduct(p1, p2, p3):
    return p1.x * (p2.y - p3.y) + p2.x * (p3.y - p1.y) + p3.x * (p1.y - p2.y)

class Hull:
    def __init__(self, point_list):
        self.hull = []
        self.points = [Point(p[0], p[1]) for p in set(tuple(p) for p in point_list)]

        if len(self.points) > 3:
            self._calculate()
        else:
            self.hull = self.points

    def _calculate(self):
        zero = min([p.swap() for p in self.points]).swap()

        def sort_key(a, b):
            o = crossProduct(zero, a, b)
            if o == 0:
                dist_a = dist((zero.x, zero.y), (a.x, a.y))
                dist_b = dist((zero.x, zero.y), (b.x, b.y))
                if dist_a == dist_b:
                    return 0
                return -1 if dist_a < dist_b else 1
            return -1 if o > 0 else 1

        self.sorted_points = sorted(self.points, key=argcomp2(sort_key))

        self.hull = [self.sorted_points[0]]
        for p in self.sorted_points[1:]:
            while len(self.hull) >= 2 and crossProduct(self.hull[-2], self.hull[-1], p) <= 0:
                self.hull.pop()
            self.hull.append(p)
    
    def getArea(self):
        area = 0
        for i in range(2, len(self.hull)):
            area += crossProduct(self.hull[0], self.hull[i - 1], self.hull[i])
        return abs(area) / 2

def convex_hull_area(pointlist):
    hull = Hull(pointlist)
    return round(hull.getArea(), 2)