#include <set>
#include <vector>
#include <iostream>
#include <algorithm>

enum EventType {
    MIN_UPDATE,
    MAX_UPDATE
};

int main() {
    std::ios_base::sync_with_stdio(false);
    std::cin.tie(NULL);
    std::cout.tie(NULL);

    long long answer = 0;

    int n;
    std::cin >> n;

    std::vector<std::pair<int, int>> min_stack(1, {-1, -1}), max_stack(1, {n, -1});
    std::set<std::pair<int, int>> events({{-1, MIN_UPDATE}, {-1, MAX_UPDATE}});

    int range_len = 0;
    for(int i = 0; i < n; ++i) {
        int p;
        std::cin >> p;


        while (min_stack.back().first > p) {
            // WE GOT A NEW MINIMUM
            auto event_it = events.lower_bound({min_stack.back().second, MIN_UPDATE});
            if (event_it != events.begin()) {
                auto prev_it = std::prev(event_it);
                // WE GOT A NEW RANGE
                range_len -= (event_it->first - prev_it->first);
            }
            min_stack.pop_back();
            events.erase(event_it);
        }

        range_len += (i - events.rbegin()->first);
        events.insert({i, MIN_UPDATE});
        min_stack.push_back({p, i});

        while (max_stack.back().first < p) {
            // WE GOT A NEW MAXIMUM
            auto event_it = events.lower_bound({max_stack.back().second, MAX_UPDATE});
            if (event_it != events.begin()) {
                auto prev_it = std::prev(event_it);
                if (event_it != events.end() && std::next(event_it) != events.end()) {
                    auto next_it = std::next(event_it);

                    if (next_it->second == MIN_UPDATE) {
                        // WE GOT A NEW RANGE
                        range_len += (event_it->first - prev_it->first);
                    }
                }
            }
            max_stack.pop_back();
            events.erase(event_it);
        }
        events.insert({i, MAX_UPDATE});
        max_stack.push_back({p, i});

        answer += range_len;
    }

    std::cout << (answer - n) << std::endl;
    return 0;
}