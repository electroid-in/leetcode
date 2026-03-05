class Solution(object):
    def minOperations(self, s):
        """
        :type s: str
        :rtype: int
        """
        # Count changes if pattern starts with '0'
        count0 = 0  # pattern: 0101...
        count1 = 0  # pattern: 1010...

        for i, char in enumerate(s):
            expected0 = '0' if i % 2 == 0 else '1'
            expected1 = '1' if i % 2 == 0 else '0'

            if char != expected0:
                count0 += 1
            if char != expected1:
                count1 += 1

        return min(count0, count1)