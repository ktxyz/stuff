class Solution:
    def getWordsInLongestSubsequence(self, n: int, words, groups):
        def hamming_distance(a, b):
            if len(a) != len(b):
                return -1
            return sum([1 for i in range(len(a)) if a[i] != b[i]])
        
        idx = {}
        for i in range(n):
            idx[words[i]] = i
        
        graph = [[] for i in range(n)]
        for i in range(n):
            for j in range(i + 1, n):
                if groups[i] != groups[j] and hamming_distance(words[i], words[j]) == 1:
                    graph[i] += [j]
        
        in_degree = [0] * n
        for i in range(n):
            for j in graph[i]:
                in_degree[j] += 1
        
        queue = []
        for i in range(n):
            if in_degree[i] == 0:
                queue.append(i)
        
        topo_order = []
        while queue:
            node = queue.pop(0)
            topo_order.append(node)
            for neighbor in graph[node]:
                in_degree[neighbor] -= 1
                if in_degree[neighbor] == 0:
                    queue.append(neighbor)
        
        dist = [0] * n
        prev = [-1] * n
        max_dist_node = 0
        for node in topo_order:
            for neighbor in graph[node]:
                if dist[neighbor] < dist[node] + 1:
                    dist[neighbor] = dist[node] + 1
                    prev[neighbor] = node
                    if dist[neighbor] > dist[max_dist_node]:
                        max_dist_node = neighbor
        
        path = []
        node = max_dist_node
        while node != -1:
            path.append(words[node])
            node = prev[node]
        
        return path[::-1]
