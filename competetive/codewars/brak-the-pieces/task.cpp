#include "task.h"
#include <iostream>

int main() {
    std::string &&shape = join("\n", 
                  {"                 ",
                   "   +-----+       ",
                   "   |     |       ",
                   "   |     |       ",
                   "   +-----+-----+ ",
                   "         |     | ",
                   "         |     | ",
                   "         +-----+ "});

    std::vector<std::string> &&pieces = break_piece(shape);
    std::cout << "RESULTS: " << pieces.size() << std::endl;
    for(auto &piece : pieces) {
        std::cout << "PIECE:\n";
        std::cout << piece << std::endl;
    }

    return 0;
}