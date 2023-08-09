#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <vector>
#include <map>

constexpr int INF = 1 << 30;


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int n;
    std::cin >> n;
    std::string xor_division(n, '0');

    std::vector<int> vec;
    for(int i = 0; i < n; ++i) {
        int a;
        std::cin >> a;
        vec.push_back(a);
    }

    if (n == 2) {
        std::cout << "10" << std::endl;
        return 0;
    }

    auto is_valid_offset = [&vec](int offset) {
        bool is_valid = false;
        std::unordered_map<int, int> m;

        for(auto x : vec) {
            m[x >> offset] += 1;
            if (m[x >> offset] == 3) {
                is_valid = true;
                break;
            }
        }

        return is_valid;
    };

    int offset = 30;
    for(int i = 0; i < 32; ++i) {
        if (is_valid_offset(i)) {
            offset = i;
            break;
        }
    }

    std::map<int, std::vector<int>> m;
    for(int i = 0; i < n; ++i)
        m[vec[i] >> offset].push_back(i);

    auto get_bits = [](int x, int min_size) -> std::vector<bool> {
        std::vector<bool> bits;
        while(x) {
            bits.push_back(x & 1);
            x >>= 1;
        }
        std::reverse(bits.begin(), bits.end());

        while (bits.size() < min_size)
            bits.push_back(0);

        return bits;
    };

    for(auto& [_, v] : m) {
        std::vector<int> values;
        for(auto x : v)
            values.push_back(vec[x]);

        int group_minimum = 0;
        auto division = get_bits(0, v.size());

        for(int i = 0; i < (1 << v.size()); ++i) {
            auto div = get_bits(i, v.size());

            std::vector<int> left;
            std::vector<int> right;

            for(int j = 0; j < div.size(); ++j) {
                if (div[j])
                    left.push_back(values[j]);
                else
                    right.push_back(values[j]);
            }

            int left_min = INF;
            for(int k = 0; k < left.size(); ++k)
                for(int l = k + 1; l < left.size(); ++l)
                    left_min = std::min(left_min, left[k] ^ left[l]);

            int right_min = INF;
            for(int k = 0; k < right.size(); ++k)
                for(int l = k + 1; l < right.size(); ++l)
                    right_min = std::min(right_min, right[k] ^ right[l]);
            
            if (std::min(left_min, right_min) > group_minimum) {
                group_minimum = std::min(left_min, right_min);
                division = div;
            }
        }

        for(int i = 0; i < v.size(); ++i)
            if (division[i])
                xor_division[v[i]] = '1';
    }

    std::cout << xor_division << std::endl;

    return 0;
}