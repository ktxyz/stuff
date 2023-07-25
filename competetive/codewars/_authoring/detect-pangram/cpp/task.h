#include <string>
#include <algorithm>

bool is_pangram(std::string s)
{
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) { return !isalpha(c); }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    std::sort(s.begin(), s.end());
    return std::unique(s.begin(), s.end()) - s.begin() == 26;
}