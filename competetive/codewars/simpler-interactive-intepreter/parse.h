#pragma once
#include <vector>
#include <map>

#include "tree.h"


class Parser {
private:
    const std::vector<Token>& tokens;
    size_t currentTokenIndex = 0;
    std::map<std::string, long double> variables;  // Store variable values

    Token peek() const {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex];
        }
        return Token{END_OF_FILE};
    }

    Token consume() {
        if (currentTokenIndex < tokens.size()) {
            return tokens[currentTokenIndex++];
        }
        throw std::runtime_error("Unexpected end of tokens.");
    }

    std::unique_ptr<ASTNode> parseExpression();
    std::unique_ptr<ASTNode> parseTerm();
    std::unique_ptr<ASTNode> parseFactor();

public:
    explicit Parser(const std::vector<Token>& tkns) : tokens(tkns) {}
    std::unique_ptr<ASTNode> parse();
};

std::unique_ptr<ASTNode> Parser::parseExpression() {
    auto left = parseTerm();
    
    #ifdef DEBUG
        std::cout << "left: " << left->toString() << std::endl;
    #endif

    while (true) {
        Token token = peek();

        #ifdef DEBUG
            std::cout << "token: " << tokenToString(token.type) << std::endl;
        #endif

        switch (token.type) {
            case OPERATOR_PLUS:
            case OPERATOR_MINUS:
                consume();  // Consume the operator token
                left = std::move(std::make_unique<BinaryOpNode>(token.type, std::move(left), parseTerm()));
                break;
            default:
                return left;
        }
    }
}

std::unique_ptr<ASTNode> Parser::parseTerm() {
    Token token = peek();

    // Handling unary minus
    if (token.type == OPERATOR_MINUS) {
        consume();  // consume the '-' token
        return std::make_unique<UnaryOpNode>(token.type, parseTerm());
    }

    auto left = parseFactor();
    while (true) {
        Token token = peek();
        
        switch (token.type) {
            case OPERATOR_MUL:
            case OPERATOR_DIV:
            case OPERATOR_MOD:
                consume();  // Consume the operator token
                left = std::move(std::make_unique<BinaryOpNode>(token.type, std::move(left), parseFactor()));
                break;
            default:
                return left;
        }
    }
}

std::unique_ptr<ASTNode> Parser::parseFactor() {
    Token token = peek();

    // Handling unary minus
    if (token.type == OPERATOR_MINUS) {
        consume();  // consume the '-' token
        return std::make_unique<UnaryOpNode>(token.type, parseFactor());
    }

    token = consume(); // Moved the consume here after checking for unary minus

    switch (token.type) {
        case NUMBER:
            return std::make_unique<NumberNode>(token.number);
        case IDENTIFIER:
            if (peek().type == OPERATOR_EQ) {
                consume();  // Consume the '=' token
                std::string varName(token.identifier);
                return std::make_unique<AssignmentNode>(varName, parseExpression());
            }
            return std::make_unique<VariableNode>(token.identifier);
        case L_BRACKET:
        {
            auto node = parseExpression();
            if (consume().type != R_BRACKET) {
                throw std::runtime_error("Expected closing parenthesis.");
            }
            return node;
        }
        case END_OF_FILE:
            return nullptr;
        default:
            throw std::runtime_error("Unexpected token in parseFactor.");
    }
}



std::unique_ptr<ASTNode> Parser::parse() {
    return parseExpression();
}
