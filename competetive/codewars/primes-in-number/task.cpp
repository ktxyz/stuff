#include <string>
#include <vector>
#include <algorithm>
#include <cmath>

class PrimeDecomp
{
public:
    static bool is_prime(int k) {
        if (k < 2) return false;
        for (int i = 2; i <= sqrt(k); ++i) {
            if (k % i == 0) return false;
        }
        return true;
    }

    static std::string factors(int lst) {
        std::vector<std::pair<int, int>> primes;

        for(int i = 2; i <= sqrt(lst); ++i) {
            if (is_prime(i)) {
                int count = 0;
                while (lst % i == 0) {
                    lst /= i;
                    ++count;
                }
                if (count > 0) primes.push_back(std::make_pair(i, count));
            }
        }

        if (lst > 1) primes.push_back(std::make_pair(lst, 1));

        std::string result;
        for(auto &p : primes) {
            if (p.second == 1) {
                result += "(" + std::to_string(p.first) + ")";
            } else {
                result += "(" + std::to_string(p.first) + "**" + std::to_string(p.second) + ")";
            }
        }

        return result;
    }
};
