def word2num(word):
    res = 0
    for ch in word:
        res |= (1<<(ord(ch)-ord('a')))
    return res

class Solution:
    def findNumOfValidWords(self, words, puzzles):
        ch_dict = [0] * (1<<26)
        for word in words:
            res = 0
            for ch in word:
                res |= (1<<(ord(ch)-ord('a')))
            ch_dict[res] += 1
        ans = []
        for puz in puzzles:
            puz_num = 0
            for ch in puz:
                puz_num |= (1<<(ord(ch)-ord('a')))
            res = 0
            bit = puz_num
            while True:
                if not bit: break
                if (bit >> (ord(puz[0])-ord('a')) & 1 == 1):
                    res += ch_dict[bit]
                bit = (bit - 1) & puz_num
            ans.append(res)
        return ans

if __name__=="__main__":
    solver = Solution()
