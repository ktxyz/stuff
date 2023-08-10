from typing import List


class Solution:
    def fullJustify(self, words: List[str], maxWidth: int) -> List[str]:
        def add_spaces(words, maxWidth, is_last=False):
            if is_last or len(words) == 1:
                return ' '.join(words).ljust(maxWidth)
            
            total_spaces = maxWidth - sum(len(word) for word in words)
            gaps = len(words) - 1
            spaces_between_words = total_spaces // gaps
            extra_spaces = total_spaces % gaps
            
            result = words[0]
            for i in range(1, len(words)):
                spaces = spaces_between_words + (1 if i <= extra_spaces else 0)
                result += ' ' * spaces + words[i]
            
            return result
        
        result = []
        current_line = []
        current_length = 0
        
        for word in words:
            if current_length + len(word) + len(current_line) <= maxWidth:
                current_line.append(word)
                current_length += len(word)
            else:
                result.append(add_spaces(current_line, maxWidth))
                current_line = [word]
                current_length = len(word)
        
        result.append(add_spaces(current_line, maxWidth, is_last=True))
        return result
