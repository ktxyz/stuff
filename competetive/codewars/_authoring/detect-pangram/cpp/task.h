#include <string>
#include <numeric>
#include <algorithm>

bool is_pangram(std::string s)
{
    std::transform(s.begin(), s.end(), s.begin(), [](char c) { return std::tolower(c); });
    std::string ascii_string(26, 'a');
    std::iota(ascii_string.begin(), ascii_string.end(), 'a');
    return std::all_of(ascii_string.begin(), ascii_string.end(), [&s](char c) {
        return s.find(c) != s.npos;
    });
}
