#ifndef PMERGEME_HPP
#define PMERGMEE_HPP

#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <climits>


class PmergeMe{
    private:
        std::vector<int > seq;
    
    public:
        PmergeMe();
        PmergeMe(const char **args, size_t seqSize);
        PmergeMe(const PmergeMe& other);
        ~PmergeMe();

        PmergeMe&    operator=(const PmergeMe& other);
        std::vector<int >                   GenerateIndices(std::vector<int > JkSeq, size_t size);
        std::vector<int >                   GenerateJacobSthalSeq(size_t PendSeqSize);
        void                                TakeSequence(const char **args, size_t seqSize);
        int                                 trim_StrToNumber(const std::string& s);
        std::vector<int>                    StartSorting(std::vector<int> Numlist);
        std::vector<std::pair<int , int> >  makePairs(std::vector<int> Numlist); 

        class NonNumberArgument: public std::exception{
            public:
                const char *what() const throw(){
                    return "The Programme expect Positive integers.";
                }
        };
        class OutOfRnage: public std::exception{
            public:
                const char *what() const throw(){
                    return "The Programme expect Positive integers: [0, 2147483647].";
                }
        };
};

#endif