#include <string>
#include <algorithm>

bool is_pangram(std::string s)
{
    // only letters, have to remove all other characters
    s.erase(std::remove_if(s.begin(), s.end(), [](char c) { return !isalpha(c); }), s.end());
    std::transform(s.begin(), s.end(), s.begin(), tolower);
    std::sort(s.begin(), s.end());
    return std::unique(s.begin(), s.end()) - s.begin() == 26;
}