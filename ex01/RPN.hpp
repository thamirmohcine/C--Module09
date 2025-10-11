#ifndef RPN_HPP
#define RPN_hpp


#include <iostream>
#include <stack>

class RPN{
    private:
        std::stack<int> s;
    public:
        RPN();
        RPN(const char *Expression);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        void    ParseInput();
        void    ProcessExpression();

};



#endif 