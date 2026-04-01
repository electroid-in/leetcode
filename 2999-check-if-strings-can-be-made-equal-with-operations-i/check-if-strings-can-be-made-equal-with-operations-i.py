class Solution:
    def canBeEqual(self, s1: str, s2: str) -> bool:
        even_s1 = [s1[0], s1[2]]
        odd_s1  = [s1[1], s1[3]]
        even_s2 = [s2[0], s2[2]]
        odd_s2  = [s2[1], s2[3]]
        
        return sorted(even_s1) == sorted(even_s2) and sorted(odd_s1) == sorted(odd_s2)