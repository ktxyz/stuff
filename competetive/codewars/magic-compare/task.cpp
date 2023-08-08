#include <iostream>
#include <cmath>
#include <vector>
#include <random>
#include <ctime>

// #define LOCAL_TASK
#include "task.h"


void testMagicCompare() {
    using MagicInt = MagicCompare<int>;
    using MagicDouble = MagicCompare<double>;

    // setup random device
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dis(2, 1000);

    while (true) {
        std::vector<int> values;
        std::vector<int> operators;
        int n = dis(gen);

        for(int i = 0; i < n; ++i) {
            values.push_back(dis(gen));
        }

        operators.push_back(-1);
        for(int i = 0; i < n - 1; ++i) {
            operators.push_back(dis(gen) % 8);
        }

        auto operator_char = [](int op) -> std::string {
            switch(op) {
                case 0:
                    return "<";
                case 1:
                    return ">";
                case 2:
                    return "<=";
                case 3:
                    return ">=";
                case 4:
                    return "==";
                case 5:
                    return "!=";
                case 6:
                    return "*";
                case 7:
                    return "/";
                default:
                    return "";
            }
        };

        std::cout << "-------TEST---------" << std::endl;
        std::cout << values[0] << " ";
        for(int i = 1; i < n; ++i)
            std::cout << operator_char(operators[i]) << " " << values[i] << " ";
        std::cout << std::endl;

        int val = values[0];
        MagicInt magic_val = val;

        bool manual_val = true;
        for(int i = 1; i < values.size(); ++i) {
            switch(operators[i]) {
                case 0:
                    manual_val &= (val < values[i]);
                    magic_val = (magic_val < values[i]);
                    break;
                case 1:
                    manual_val &= (val > values[i]);
                    magic_val = (magic_val > values[i]);
                    break;
                case 2:
                    manual_val &= (val <= values[i]);
                    magic_val = (magic_val <= values[i]);
                    break;
                case 3:
                    manual_val &= (val >= values[i]);
                    magic_val = (magic_val >= values[i]);
                    break;
                case 4:
                    manual_val &= (val == values[i]);
                    magic_val = (magic_val == values[i]);
                    break;
                case 5:
                    manual_val &= (val != values[i]);
                    magic_val = (magic_val != values[i]);
                    break;
                case 6:
                    magic_val = (magic_val * values[i]);
                    values[i] *= val;
                    break;
                case 7:
                    if (values[i] == 0)
                        values[i] = 1;
                    magic_val = (magic_val / values[i]);
                    values[i] = val / values[i];
                    break;
                default:
                    break;
            }

            val = values[i];
        }

        if ((manual_val && magic_val) || (!manual_val && !magic_val)) {
            std::cout << "Test passed!" << std::endl;
        } else {
            std::cout << "Test failed!" << std::endl;
            std::cout << "Manual value: " << (manual_val ? "true" : "false") << std::endl;
            std::cout << "Magic value: " << (magic_val ? "true" : "false") << std::endl;
            return;
        }
    }
}


void basic_relations() {
    using MagicInt = MagicCompare<int>;
    MagicInt a = 3;
    bool res_4lta = (4 < a);
    std::cout << "Result of (4 < a): " << res_4lta << " | should be " << false << std::endl; // Should be false

    bool res_5gtalt7neqa = (5 > a < 7 != a);
    std::cout << "Result of (5 > a < 7 != a): " << res_5gtalt7neqa << " | should be " << true << std::endl; // Should be true
}

void int_practical_use() {
    using Integer = MagicCompare<int>;
    std::vector<int> interval;

    for (Integer i = 0; i < 5; ++i) {
        if (5 < (i * i) < 17) {
            interval.push_back(i);
        }
    }

    std::cout << "Numbers in the interval (for integers): ";
    for (const int& val : interval) {
        std::cout << val << " ";
    }
    std::cout << std::endl;
}

void double_practical_use() {
    using Float = MagicCompare<double>;
    std::vector<double> interval;

    for (Float x = 0; x < 1.0; x += 0.01) {
        if (sin(x) < (exp(x) * x) < cos(x)) {
            interval.push_back(x);
        }
    }

    std::cout << "Numbers in the interval (for doubles): ";
    for (const double& val : interval) {
        std::cout << round(100 * val) << " ";
    }
    std::cout << std::endl;
}

int main() {
    testMagicCompare();
    // basic_relations();
    // int_practical_use();
    // double_practical_use();

    return 0;
}
