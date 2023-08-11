from typing import List


class Solution:
    def findSubstring(self, s: str, words: List[str]) -> List[int]:
        words.sort()
        word_length = len(words[0])

        idxs = []
        for i in range(0, len(s) - len(words) * word_length + 1):
            next_words = sorted(s[i + word_length * x : i + (x + 1) * word_length] for x in range(0, len(words)))
            if next_words == words:
                idxs.append(i)

        return idxs
