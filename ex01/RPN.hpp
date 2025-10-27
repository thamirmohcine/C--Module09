#ifndef RPN_HPP
#define RPN_hpp


#include <iostream>
#include <stack>
#include <climits>


class RPN{
    private:
        std::stack<double> s;
    public:
        RPN();
        RPN(const std::string &PostfixExpression);
        RPN(const RPN& other);
        RPN& operator=(const RPN& other);
        ~RPN();

        void    ParseInput(const std::string &PostfixExpression);
        void    Exec(const std::string &PostfixExpression);
        int     TopPop();
        void    CaluculePush(char a);
        class ContainInvalidCharacter : public std::exception{
            public:
                const char *what() const throw(){
                    return ("The RPN Expression Contain Invalid Chars:\n\
                        Expected: Only Numbers Less Than 10 and Only These Operations'+ - / *'.");
                }
        };
        class ExpressionInvalid : public std::exception{
            public:
                const char *what() const throw(){
                    return ("The Expression Is Invalid:\n\
                        The Expression Must Be A Valid Reverse Polish.");
                }
        };
        class DivisionByZero : public std::exception{
            public:
                const char *what() const throw(){
                    return ("Exception A Devision By Zero Occure.");
                }
        };
        class ResultOverflow : public std::exception{
            public:
                const char *what() const throw(){
                    return ("Exception A Overflowed Result.");
                }
        };
};



#endif 