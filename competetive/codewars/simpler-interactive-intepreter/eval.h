#pragma once
#include <cmath>

#include "parse.h"


class Evaluator {
private:
    std::map<std::string, long double>& variables;

    long double visit(ASTNode* node) {
        if (auto num = dynamic_cast<NumberNode*>(node)) {
            return num->value;
        } else if (auto var = dynamic_cast<VariableNode*>(node)) {
            return visitVariable(var);
        } else if (auto binOp = dynamic_cast<BinaryOpNode*>(node)) {
            return visitBinaryOp(binOp);
        } else if (auto assign = dynamic_cast<AssignmentNode*>(node)) {
            return visitAssignment(assign);
        } else if (auto unaryOp = dynamic_cast<UnaryOpNode*>(node)) {
            return visitUnaryOp(unaryOp);
        }
        throw std::runtime_error("Unknown node type.");
    }

    long double visitVariable(VariableNode* varNode);
    long double visitBinaryOp(BinaryOpNode* binNode);
    long double visitAssignment(AssignmentNode* assignNode);
    long double visitUnaryOp(UnaryOpNode* unaryNode);

public:
    explicit Evaluator(std::map<std::string, long double>& vars) : variables(vars) {}
    long double evaluate(ASTNode* root) {
        return visit(root);
    }
};

long double Evaluator::visitVariable(VariableNode* varNode) {
    if (variables.find(varNode->name) == variables.end()) {
        throw std::runtime_error("ERROR: Invalid identifier. No variable with name '" + varNode->name + "' was found.");
    }
    return variables[varNode->name];
}

long double mod(long double a, int b) {
    int c = abs(a);
    int d = abs(b);

    int r = c % d;
    if ((a < 0 && b > 0) || (a > 0 && b < 0)) r = -r;
    return r;
}

long double Evaluator::visitBinaryOp(BinaryOpNode* binNode) {
    long double left = visit(binNode->left.get());
    long double right = visit(binNode->right.get());

    #ifdef DEBUG
    switch(binNode->op) {
        case OPERATOR_PLUS:
            std::cout << "left: " << left << " + right: " << right << std::endl;
            break;
        case OPERATOR_MINUS:
            std::cout << "left: " << left << " - right: " << right << std::endl;
            break;
        case OPERATOR_MUL:
            std::cout << "left: " << left << " * right: " << right << std::endl;
            break;
        case OPERATOR_DIV:
            std::cout << "left: " << left << " / right: " << right << std::endl;
            break;
        case OPERATOR_MOD:
            std::cout << "left: " << left << " % right: " << right << std::endl;
            break;
        default:
            throw std::runtime_error("Unknown binary operator.");
    }
    #endif


    switch (binNode->op) {
        case OPERATOR_PLUS:
            return left + right;
        case OPERATOR_MINUS:
            return left - right;
        case OPERATOR_MUL:
            return left * right;
        case OPERATOR_DIV:
            if (right == 0) throw std::runtime_error("Division by zero.");
            return left / right;
        case OPERATOR_MOD:
            return fmod(left, right);
        default:
            throw std::runtime_error("Unknown binary operator.");
    }
}

long double Evaluator::visitAssignment(AssignmentNode* assignNode) {
    long double value = visit(assignNode->value.get());
    variables[assignNode->varName] = value;
    return value;
}

long double Evaluator::visitUnaryOp(UnaryOpNode* unaryNode) {
    if (unaryNode->op == OPERATOR_MINUS) {
        return -visit(unaryNode->operand.get());
    }
    throw std::runtime_error("Unknown unary operator.");
}
