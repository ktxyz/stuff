#include <algorithm>
#include <iostream>
#include <vector>
#include <set>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t;
    std::cin >> t;
    while(t--) {
        int n, m;
        std::vector<int> b;
        std::vector<int> a;

        std::cin >> n;
        for(int i = 0; i < (n * (n - 1)) / 2; i++) {
            std::cin >> m;
            b.push_back(m);
        }
        std::sort(b.begin(), b.end());
        std::multiset<int> b_m_set(b.begin(), b.end());

        auto it = std::unique(b.begin(), b.end());
        b.resize(std::distance(b.begin(), it));

        auto create_pairs = [&b_m_set, &a](int v) {
            for(auto &u : a) {
                auto k = std::min(u, v);
                b_m_set.erase(b_m_set.find(k));
            }
            a.push_back(v);
        };

        for(int i = b.size() - 1; i >= 0; --i) {
            int val = b[i];
            create_pairs(val);
            while (b_m_set.count(val) >= 1) {
                create_pairs(val);
            }
        }

        for(auto &v : a) {
            std::cout << v << " ";
        }
        std::cout << std::endl;
    }

}