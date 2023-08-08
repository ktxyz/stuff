#pragma once
#include <string>
#include <iostream>

#include "eval.h"

double interpret(const std::string& input) {
    static std::map<std::string, long double> variables;  // Store state between calls

    std::cout << "Input: " << input << std::endl;
    auto tokens = tokenize(input);

    if (tokens.size() == 0) {
        std::cout << "No tokens." << std::endl;
        throw std::exception();
    }

    #ifdef TOKEN_DEBUG
    for (auto& token : tokens) {
        token.print();
    }
    std::cout << std::endl;
    #endif

    Parser parser(tokens);
    auto ast = parser.parse();
    
    Evaluator evaluator(variables);
    return evaluator.evaluate(ast.get());
}
