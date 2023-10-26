class Cons:
    def __init__(self, head, tail):
        self.head = head
        self.tail = tail
    
    def to_array(self):
        return [self.head] + (self.tail.to_array() if self.tail is not None else [])
      
    @classmethod
    def from_array(cls, arr):
        if arr:
            return Cons(arr[0], Cons.from_array(arr[1:]))
        return None
    
    def filter(self, fn):
        arr = self.to_array()
        return Cons.from_array([x for x in arr if fn(x)])
    
    def map(self, fn):
        arr = self.to_array()
        return Cons.from_array(list(map(fn, arr)))
