#include <vector>

void fill_paths(int v, std::vector<std::vector<short>> &G, std::vector<bool> &visited) {
    std::vector<std::pair<std::pair<int, int>, std::pair<int, int>>> delta = {
        {{0, 1}, {0, -1}},
        {{1, 0}, {-1, 0}},
        {{-1, -1}, {1, 1}},
        {{-1, 1}, {1, -1}}
    };

    int x = v % 3;
    int y = v / 3;
    for(auto &dPair : delta) {
        int nx1 = x + dPair.first.first;
        int ny1 = y + dPair.first.second;
        int nx2 = x + dPair.second.first;
        int ny2 = y + dPair.second.second;

        if (nx1 < 0 || nx1 >= 3 || ny1 < 0 || ny1 >= 3 || nx2 < 0 || nx2 >= 3 || ny2 < 0 || ny2 >= 3) continue;

        int v1 = ny1 * 3 + nx1;
        int v2 = ny2 * 3 + nx2;

        if (!visited[v1] && !visited[v2]) {
            G[v1].push_back(v2);
            G[v2].push_back(v1);
        }
    }
}

unsigned int DFS(int v, unsigned short length, std::vector<std::vector<short>> graph, std::vector<bool> visited) {
    if (length <= 0) return 1;
    visited[v] = true;

    fill_paths(v, graph, visited);
    
    unsigned int result = 0;

    for(auto &u : graph[v]) {
        if (!visited[u]) {
            result += DFS(u, length - 1, graph, visited);
        }
    }

    return result;
}

unsigned int countPatternsFrom(char firstDot, unsigned short length) {
    std::vector<int> dx = {1, -1, 0, 0, -1, -1, 1, 1, 2, 2, -2, -2, 1, -1, 1, -1};
    std::vector<int> dy = {0, 0, 1, -1, -1, 1, -1, 1, 1, -1, 1, -1, 2, 2, -2, -2};

    if (length > 9) return 0;
    std::vector<bool> visited(9, false);
    std::vector<std::vector<short>> graph(9, std::vector<short>());

    for(int y = 0; y < 3; ++y) {
        for(int x = 0; x < 3; ++x) {
            for(int i = 0; i < dx.size(); ++i) {
                int nx = x + dx[i];
                int ny = y + dy[i];
                if (nx >= 0 && nx < 3 && ny >= 0 && ny < 3) {
                    graph[y * 3 + x].push_back(ny * 3 + nx);
                }
            }
        }
    }

    return DFS(firstDot - 'A', length - 1, graph, visited);
}