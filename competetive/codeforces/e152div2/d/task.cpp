#include <iostream>
#include <algorithm>
#include <vector>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;

    std::vector<int> arr;
    std::vector<int> v[3];

    for(int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;

        arr.push_back(a);
        v[a].push_back(i);
    }

    int cost = 0;
    int position = 0;

    while(position < n) {
        bool has_left_zero = (arr[position] == 0);
        auto next_zero = std::lower_bound(v[0].begin(), v[0].end(), position + 1);

        if (next_zero == v[0].end()) {
            cost += 1;
            break;
        }

        int next_zero_pos = *next_zero;

        bool has_two_inside = true;
        auto next_two = std::lower_bound(v[2].begin(), v[2].end(), position + 1);

        if (next_two == v[2].end())
            has_two_inside = false;
        else if (*next_two > next_zero_pos)
            has_two_inside = false;
        
        cost += 1;

        // if we have a zero on the left, and zero on the right, and two inside
        // we can move past the zero on the right
        if (has_left_zero) {
            if (has_two_inside) {
                position = next_zero_pos + 1;
            } else {
                position = next_zero_pos;
            }
        } else {
            position = next_zero_pos + 1;
        }
    }

    std::cout << cost << "\n";
    return 0;
}