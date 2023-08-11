class Solution:
    def isIsomorphic(self, s: str, t: str) -> bool:
        if len(s) != len(t):
            return False
        
        char_mapping = {}
        used_chars = set() 
    
        for i in range(len(s)):
            if s[i] in char_mapping:
                if char_mapping[s[i]] != t[i]:
                    return False
            else:
                if t[i] in used_chars:
                    return False
                char_mapping[s[i]] = t[i]
                used_chars.add(t[i])
        
        return True