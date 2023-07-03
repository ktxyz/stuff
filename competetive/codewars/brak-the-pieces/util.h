#pragma once
#include <string>
#include <vector>
#include <iostream>
#define DEBUG(x) std::cerr << x 

std::string join(const std::string &sep, const std::vector<std::string> &to_join) {
    std::string res = "";
    for(auto &s : to_join) {
        res += s + sep;
    }
    res.pop_back();
    return res;
}

std::vector<std::string> split_lines(const std::string &to_split) {
    std::vector<std::string> res;
    std::string curr_line = "";
    for(auto &c : to_split) {
        if(c == '\n') {
            res.push_back(curr_line);
            curr_line = "";
        } else {
            curr_line += c;
        }
    }

    if(!curr_line.empty()) {
        res.push_back(curr_line);
    }

    return res;
}