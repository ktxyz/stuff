#include <vector>
#include <algorithm>

using std_pair = std::pair<int, int>;


class Solution {
public:
    void rotate(std::vector<std::vector<int>>& matrix) {
        int width = matrix.size();

        for(int y = 0; y < width / 2; ++y) {
            for(int x = y; x < width - y - 1; ++x) {
                std_pair pos1 = {y, x};
                std_pair pos2 = {x, width - y - 1};
                std_pair pos3 = {width - y - 1, width - x - 1};
                std_pair pos4 = {width - x - 1, y};

                auto swap = [&](std_pair p1, std_pair p2) {
                    std::swap(matrix[p1.first][p1.second], matrix[p2.first][p2.second]);
                };

                swap(pos1, pos2);
                swap(pos1, pos3);
                swap(pos1, pos4);
            }
        }
    }
};