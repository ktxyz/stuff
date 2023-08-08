#include <iostream>

#define DEBUG
#define TOKEN_DEBUG
#include "task.h"


int main() {
    std::cout << "STARTING TESTS" << std::endl;
    if (interpret("1 + 1") != 2) {
        std::cout << "1 + 1 != 2" << std::endl;
        return 1;
    }

    if (interpret("2 * 2") != 4) {
        std::cout << "2 * 2 != 4" << std::endl;
        return 1;
    }

    if (interpret("1 + 2 * 3") != 7) {
        std::cout << "1 + 2 * 3 != 7" << std::endl;
        return 1;
    }

    if (interpret("1 + 2 * 3 + 4") != 11) {
        std::cout << "1 + 2 * 3 + 4 != 11" << std::endl;
        return 1;
    }

    if (interpret("x = 1") != 1) {
        std::cout << "x = 1 != 1" << std::endl;
        return 1;
    }

    if (interpret("x") != 1) {
        std::cout << "x != 1" << std::endl;
        return 1;
    }

    if (interpret("x + 3") != 4) {
        std::cout << "x + 3 != 4" << std::endl;
        return 1;
    }

    if (interpret("51 + -94 * -74 % -23 % -53 + 23 - 98 + 91") != 77) {
        std::cout << "51 + -94 * -74 % -23 % -53 + 23 - 98 + 91 != 77 | = " << interpret("51 + -94 * -74 % -23 % -53 + 23 - 98 + 91") << std::endl;
        return 1;
    }

    if (interpret("95 / -34 - 55 % 4 - 13 / -97 + -90 + 51") == 55) {
        std::cout << "95 / -34 - 55 % 4 - 13 / -97 + -90 + 51 == 55 | = " << interpret("95 / -34 - 55 % 4 - 13 / -97 + -90 + 51") << std::endl;
        return 1;
    }

    if (interpret("-83 % 43") != -40) {
        std::cout << "-83 % 43 != -40 | = " << interpret("-83 % 43") << std::endl;
        return 1;
    }

    if (std::abs(interpret("68 * -55 / 99 + -83 % 43 / 12 * 96 * -35") - (long double)11162.2) > .5) {
        std::cout << "68 * -55 / 99 + -83 % 43 / 12 * 96 * -35 != 11162.2f | = " << interpret("68 * -55 / 99 + -83 % 43 / 12 * 96 * -35") << std::endl;
        return 1;
    }

    if (std::abs(interpret("-44 / -37 * -62 * 43 / -81 / 25 % -87 * -76") - -118.987) > .5) {
        std::cout << "-44 / -37 * -62 * 43 / -81 / 25 % -87 * -76 != -118.987 | = " << interpret("-44 / -37 * -62 * 43 / -81 / 25 % -87 * -76") << std::endl;
        return 1;
    }

    if (interpret("-48 % -96 + 49 * 97 % 53 * -49 % 75 * 57") == 0) {
        std::cout << "-48 % -96 + 49 * 97 % 53 * -49 % 75 * 57 == 0 | = " << interpret("-48 % -96 + 49 * 97 % 53 * -49 % 75 * 57") << std::endl;
        return 1;
    }

    if (interpret("(-42) / (-65 / 75 - (32)) + (-10 * -((((77 - -43)))) - -81)") == 0) {
        std::cout << "(-42) / (-65 / 75 - (32)) + (-10 * -((((77 - -43)))) - -81) == 0 | = " << interpret("(-42) / (-65 / 75 - (32)) + (-10 * -((((77 - -43)))) - -81)") << std::endl;
        return 1;
    }

    if (std::abs((interpret("-(-28) + (89 + 9 / (66)) % (-97 - (((-(-30 % 14)))) + 28)") - 46.1364)) > 0.5) {
        std::cout << "-(-28) + (89 + 9 / (66)) % (-97 - (((-(-30 % 14)))) + 28) == 0 | = " << interpret("-(-28) + (89 + 9 / (66)) % (-97 - (((-(-30 % 14)))) + 28)") << std::endl;
        return 1;
    }

    if (std::abs((interpret("-(91) * (-48 + -58 / -(25)) * (-8 / -(((-(-16 * -96)))) % 98)") - -21.6504)) > 0.5) {
        std::cout << "-(91) * (-48 + -58 / -(25)) * (-8 / -(((-(-16 * -96)))) % 98) == 0 | = " << interpret("-(91) * (-48 + -58 / -(25)) * (-8 / -(((-(-16 * -96)))) % 98)") << std::endl;
        return 1;
    }

    std::vector<std::string> vec = {"jhjn = 79 + -(61 * -68 % 32) % -71",
    "nktb = 96 - -(-58 - -50 - 35) / -51",
    "rdzgy = -17 - -(78 * 42 - -94) / 19",
    "libg = 94 - (-3 * 9 + 93) % -74",
    "vqq = -59 % -(-54 + -6 / -69) - -26",
    "-jhjn % rdzgy * -nktb % -libg + vqq"};

    for(int i = 0; i < vec.size() - 1; ++i) {
        interpret(vec[i]);
    }

    if (std::abs(interpret(vec.back()) - 32.3836) > 0.5) {
        std::cout << vec.back() << " != 32.3836 | = " << interpret(vec.back()) << std::endl;
        return 1;
    }

    std::cout << "All tests passed" << std::endl;
    return 0;
}