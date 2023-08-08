#include <iostream>
#include <vector>
#include <algorithm>


int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    int t;
    std::cin >> t;
    while(t--) {
        int n;
        std::cin >> n;

        std::vector<int> answers(n + 1, 0);
        std::vector<std::pair<int, int>> arr;
        arr.push_back({0, 0});

        for(int i = 0; i < n; i++) {
            int temp;
            std::cin >> temp;
            arr.push_back({temp, i + 1});
        }

        std::sort(arr.begin(), arr.end());

        std::vector<int> prefix_sum(n + 1, 0);
        for(int i = 1; i <= n; i++) {
            prefix_sum[i] = prefix_sum[i - 1] + arr[i].first;
        }

        int answer = n;
        for(int i = 1; i <= n; ++i) {
            answers[arr[i].second] = n + arr[i].first * (2 * i - n) - 2 * prefix_sum[i] + prefix_sum[n];
        }

        for(int i = 1; i <= n; ++i)
            std::cout << answers[i] << " ";
        std::cout << "\n";
    }

    return 0;
}