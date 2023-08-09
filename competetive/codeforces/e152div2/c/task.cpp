#include <iostream>
#include <string>
#include <vector>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t;
    std::cin >> t;

    while(t--) {
        int n, m;
        std::cin >> n >> m;

        std::string s;
        std::cin >> s;

        std::vector<int> zero_pos, one_pos;
        for(int i = 0; i < n; ++i) {
            if(s[i] == '0') {
                zero_pos.push_back(i + 1);
            } else {
                one_pos.push_back(i + 1);
            }
        }

        std::vector<std::pair<int, int>> q;
        for(int i = 0; i < m; ++i) {
            int l, r;
            std::cin >> l >> r;

            // We calculate actual range that this impacts

            auto first_one = std::lower_bound(one_pos.begin(), one_pos.end(), l);
            auto last_zero = std::upper_bound(zero_pos.begin(), zero_pos.end(), r);

            if (last_zero != zero_pos.begin() && std::prev(last_zero) != zero_pos.end()) {
                last_zero = std::prev(last_zero);
            } else {
                last_zero = zero_pos.end();
            }

            if (first_one == one_pos.end() || last_zero == zero_pos.end()) {
                // range doesnt impact anything
                q.push_back({0, 0});
                continue;
            }

            l = *first_one;
            r = *last_zero;

            if (l > r) {
                q.push_back({0, 0});
                continue;
            } else {
                q.push_back({l, r});
            }
        }

        std::sort(q.begin(), q.end());
        q.erase(std::unique(q.begin(), q.end()), q.end());

        std::cout << q.size() << '\n';
    }
}