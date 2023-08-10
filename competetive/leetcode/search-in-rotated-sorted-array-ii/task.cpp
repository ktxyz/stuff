#include <iostream>


#define DEBUG

#include "task.h"

int main() {
    auto sol = Solution();

    auto vec1 = std::vector<int>{2, 5, 6, 0, 0, 1, 2};
    auto vec2 = std::vector<int>{4, 4, 4, 4, 4, 4, 1, 4, 4, 4};
    auto vec3 = std::vector<int>{4, 4, 4, 4, 4, 4, 4, 4, 4, 4};
    auto vec4 = std::vector<int>{2, 2, 2, 3, 2, 2, 2};

    std::cout << sol.search(vec1, 0) << std::endl; // 4
    std::cout << sol.search(vec1, 3) << std::endl; // -1

    std::cout << sol.search(vec2, 1) << std::endl; // 6
    std::cout << sol.search(vec2, 4) << std::endl; // 0
    
    std::cout << sol.search(vec3, 1) << std::endl; // -1
    std::cout << sol.search(vec3, 4) << std::endl; // 0
    
    std::cout << sol.search(vec4, 3) << std::endl; // 3
    return 0;
}