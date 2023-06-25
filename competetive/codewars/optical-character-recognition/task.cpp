#include <fstream>

#include "task.h"

struct Test {
    std::string expected;
    int width, height;
    std::vector<unsigned> data;
};

int main() {
    std::ifstream in("data/test_input.txt");

    Test test;

    in >> test.expected;
    in >> test.width >> test.height;

    for (int i = 0; i < test.width * test.height; ++i) {
        unsigned value;
        in >> value;
        test.data.push_back(value);
    }

    Image testImage = Image(test.width, test.height, test.data);
    std::string result = ocr(testImage);
    if (result != test.expected) {
        std::cout << "Test failed: " << result << " != " << test.expected << std::endl;
        return 1;
    } else {
        std::cout << "Test passed" << std::endl;
        return 0;
    }
}