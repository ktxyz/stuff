class Solution:
    def isHappy(self, n: int) -> bool:
        def get_next(number):
            total_sum = 0
            while number > 0:
                digit = number % 10
                total_sum += digit * digit
                number //= 10
            return total_sum
        
        slow = n
        fast = n
        
        while True:
            slow = get_next(slow)
            fast = get_next(get_next(fast))
            
            if slow == fast:
                break
        
        return slow == 1
