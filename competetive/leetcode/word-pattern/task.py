class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:
        words = s.split()
        
        if len(pattern) != len(words):
            return False
        
        char_to_word = {}
        used_words = set()

        for i in range(len(pattern)):
            if pattern[i] in char_to_word:
                if char_to_word[pattern[i]] != words[i]:
                    return False
            else:
                if words[i] in used_words:
                    return False
                char_to_word[pattern[i]] = words[i]
                used_words.add(words[i])
        
        return True