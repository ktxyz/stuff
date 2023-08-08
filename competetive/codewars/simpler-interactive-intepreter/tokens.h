#pragma once
#include <vector>
#include <string>
#include <cstring>
#include <iostream>


enum TokenType {
    NUMBER,
    IDENTIFIER,
    OPERATOR_EQ,
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_MUL,
    OPERATOR_DIV,
    OPERATOR_MOD,
    L_BRACKET,
    R_BRACKET,
    END_OF_FILE,
};

struct Token {
    TokenType type;

    union {
        long double number;
        char identifier[64];
    };

    void print() {
        if (type == NUMBER)
            std::cout << "TOKEN_NUMBER: " << number << " ";
        else {
            std::string identifier_str(identifier);
            std::string type_str;
            switch(type) {
                case OPERATOR_EQ:
                    type_str = "OPERATOR_EQ";
                    break;
                case OPERATOR_PLUS:
                    type_str = "OPERATOR_PLUS";
                    break;
                case OPERATOR_MINUS:
                    type_str = "OPERATOR_MINUS";
                    break;
                case OPERATOR_MUL:
                    type_str = "OPERATOR_MUL";
                    break;
                case OPERATOR_DIV:
                    type_str = "OPERATOR_DIV";
                    break;
                case OPERATOR_MOD:
                    type_str = "OPERATOR_MOD";
                    break;
                case L_BRACKET:
                    type_str = "L_BRACKET";
                    break;
                case R_BRACKET:
                    type_str = "R_BRACKET";
                    break;
                case IDENTIFIER:
                    type_str = "IDENTIFIER";
                    break;
            }
            std::cout << "TOKEN_" << type_str << ": " << identifier_str << " ";
        }
    }
};

std::vector<Token> tokenize(const std::string& input) {
    std::string mut_input = input + "#";
    std::vector<Token> tokens;

    auto is_identifier = [](char c) {
        return (c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') || c == '_';
    };

    auto is_digit = [](char c) {
        return c >= '0' && c <= '9';
    };

    char peek = 0;
    char buffer[64];
    char *buffer_ptr = buffer;

    auto reset_buffer = [&buffer, &buffer_ptr]() {
        memset(buffer, 0, sizeof(buffer));
        buffer_ptr = buffer;
    };
    memset(buffer, 0, sizeof(buffer));

    bool had_value_token = false;
    for(int i = 0; i < input.size(); ++i) {
        if (is_digit(input[i]) || (input[i] == '-' && tokens.size() == 0) || (input[i] == '-' && !had_value_token && (i < input.size() - 1) && is_digit(input[i + 1]))) {
            if(input[i] == '-' && input[i + 1] == '(') {
                tokens.push_back({OPERATOR_MINUS});
                continue;
            } else if (input[i] == '-' && !is_digit(input[i + 1])) {
                tokens.push_back({OPERATOR_MINUS});
                continue;
            }
            
            do{
                  *buffer_ptr++ = input[i++];
            } while (is_digit(input[i]) || input[i] == '.');
            --i;

            Token token;
            token.type = NUMBER;
            token.number = atof(buffer);
            tokens.push_back(token);
            reset_buffer();

            had_value_token = true;
        } else if (is_identifier(input[i])) {
            while(is_identifier(input[i]) || is_digit(input[i])) {
                *buffer_ptr++ = input[i++];
            }
            --i;

            Token token;
            token.type = IDENTIFIER;
            strcpy(token.identifier, buffer);
            tokens.push_back(token);
            reset_buffer();

            had_value_token = true;
        } else if (input[i] == '=') {
            tokens.push_back({OPERATOR_EQ});
            had_value_token = false;
        } else if (input[i] == '+') {
            had_value_token = false;
            tokens.push_back({OPERATOR_PLUS});
        } else if (input[i] == '-') {
            had_value_token = false;
            tokens.push_back({OPERATOR_MINUS});
        } else if (input[i] == '*') {
            had_value_token = false;
            tokens.push_back({OPERATOR_MUL});
        } else if (input[i] == '/') {
            had_value_token = false;
            tokens.push_back({OPERATOR_DIV});
        } else if (input[i] == '%') {
            had_value_token = false;
            tokens.push_back({OPERATOR_MOD});
        } else if (input[i] == '(') {
            tokens.push_back({L_BRACKET});
            had_value_token = false;
        } else if (input[i] == ')') {
            tokens.push_back({R_BRACKET});
            had_value_token = true;
        }
    }

    return tokens;
}


std::string tokenToString(TokenType type) {
    switch (type) {
        case NUMBER: return "NUMBER";
        case IDENTIFIER: return "IDENTIFIER";
        case OPERATOR_EQ: return "OPERATOR_EQ";
        case OPERATOR_PLUS: return "OPERATOR_PLUS";
        case OPERATOR_MINUS: return "OPERATOR_MINUS";
        case OPERATOR_MUL: return "OPERATOR_MUL";
        case OPERATOR_DIV: return "OPERATOR_DIV";
        case OPERATOR_MOD: return "OPERATOR_MOD";
        case L_BRACKET: return "L_BRACKET";
        case R_BRACKET: return "R_BRACKET";
        case END_OF_FILE: return "END_OF_FILE";
        default: return "UNKNOWN";
    }
}
