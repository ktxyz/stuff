class Solution:
    def reverseWords(self, s: str) -> str:
        return ' '.join(reversed([w.strip() for w in s.split(' ') if w.strip() != '']))