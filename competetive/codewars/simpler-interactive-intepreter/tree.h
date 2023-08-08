#pragma once
#include <memory>
#include <string>

#include "tokens.h"

struct ASTNode {
    virtual ~ASTNode() = default;
    virtual std::string toString() const = 0;
};

struct NumberNode : ASTNode {
    long double value;
    explicit NumberNode(long double val) : value(val) {}

    std::string toString() const override {
        return std::to_string(value);
    }
};

struct VariableNode : ASTNode {
    std::string name;
    explicit VariableNode(const std::string& varName) : name(varName) {}

    std::string toString() const override {
        return name;
    }
};

struct BinaryOpNode : ASTNode {
    TokenType op;
    std::unique_ptr<ASTNode> left;
    std::unique_ptr<ASTNode> right;

    BinaryOpNode(TokenType operation, std::unique_ptr<ASTNode> l, std::unique_ptr<ASTNode> r)
        : op(operation), left(std::move(l)), right(std::move(r)) {}

    std::string toString() const override {
        return "(" + left->toString() + " " + tokenToString(op) + " " + right->toString() + ")";
    }
};

struct AssignmentNode : ASTNode {
    std::string varName;
    std::unique_ptr<ASTNode> value;

    AssignmentNode(const std::string& name, std::unique_ptr<ASTNode> val)
        : varName(name), value(std::move(val)) {}

    std::string toString() const override {
        return varName + " = " + value->toString();
    }
};

struct UnaryOpNode : ASTNode {
    TokenType op;
    std::unique_ptr<ASTNode> operand;

    UnaryOpNode(TokenType operation, std::unique_ptr<ASTNode> opnd)
        : op(operation), operand(std::move(opnd)) {}

    std::string toString() const override {
        return tokenToString(op) + operand->toString();
    }
};
