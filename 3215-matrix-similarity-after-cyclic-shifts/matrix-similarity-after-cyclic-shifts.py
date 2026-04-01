from typing import List

class Solution:
    def areSimilar(self, mat: List[List[int]], k: int) -> bool:
        m, n = len(mat), len(mat[0])
        shift = k % n  # effective shift
        if shift == 0:
            return True  # no effective shift, matrix unchanged
        
        for i, row in enumerate(mat):
            if i % 2 == 0:  # even index → left shift
                if row[shift:] + row[:shift] != row:
                    return False
            else:           # odd index → right shift
                if row[-shift:] + row[:-shift] != row:
                    return False
        return True