class Solution:
    def canConstruct(self, ransomNote: str, magazine: str) -> bool:
        letter_count = [0] * 26 

        for char in magazine:
            letter_count[ord(char) - ord('a')] += 1
        
        for char in ransomNote:
            index = ord(char) - ord('a')
            if letter_count[index] <= 0:
                return False
            letter_count[index] -= 1
        
        return True