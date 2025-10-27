#include "RPN.hpp"

RPN::RPN(){}

RPN::RPN(const std::string &PostfixExpression){
    Exec(PostfixExpression);
}

RPN::RPN(const RPN& other){
    *this = other;
}

RPN& RPN::operator=(const RPN& other){
    if (this != &other){
        this->s = other.s;
    }
    return *this;
}

RPN::~RPN(){}

int RPN::TopPop(){
    int value = s.top(); 
    s.pop();
    return value;
}

void    RPN::CaluculePush(char op){
    double b = TopPop();
    double a = TopPop();
    double result = 0;
    switch(op){
        case '+':
            result = (a + b); break;
        case '-':
            result = (a - b); break;
        case '*':
            result = (a * b); break; 
        case '/':{
            if (b == 0)
                throw DivisionByZero();
            result = (a / b); break;
        }
    }
    if (result > INT_MAX || result < INT_MIN)
        throw ResultOverflow();
    s.push(result);
}

void    RPN::ParseInput(const std::string &PostfixExpression){
    std::string ValidInput = "0123456789*-/+ ";
    std::string Nums = "0123456789";
    for (size_t i(0); i < PostfixExpression.size();i++){
        if (ValidInput.find(PostfixExpression[i]) == std::string::npos\
        || (Nums.find(PostfixExpression[i]) != std::string::npos && i+1 < PostfixExpression.size()\
            && Nums.find(PostfixExpression[i+1]) != std::string::npos)){
                throw ContainInvalidCharacter();
            }
    }
}

void    RPN::Exec(const std::string &PostfixExpression){
    ParseInput(PostfixExpression);
    std::string Operators = "*/-+";
    std::string Nums = "0123456789";
    for (size_t i(0); i < PostfixExpression.size();i++){
        if (Nums.find((PostfixExpression[i])) != std::string::npos) {
            s.push(PostfixExpression[i] - '0'); 
            continue;
        }
        if (PostfixExpression[i] == ' ') continue;
        if (Operators.find(PostfixExpression[i]) != std::string::npos){
            if (s.size() < 2)
                throw ExpressionInvalid();
            CaluculePush(PostfixExpression[i]);
        }
    }
    if (s.size() == 1)
        std::cout << TopPop() << std::endl;
}