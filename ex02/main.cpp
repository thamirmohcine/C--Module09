#include "PmergeMe.hpp"

int main(int ac, char **av){
    // // av++;
    // for (int i = 0; i < ac;i++){
    //     std::cout << av[i] << " ";
    // }
    av++;
    std::cout << "\n";
    try{
        PmergeMe a((const char **)av, ac-1);
    }
    catch(std::exception& r){
        std::cout << r.what() << "\n";
    }
}