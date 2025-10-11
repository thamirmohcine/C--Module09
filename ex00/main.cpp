#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    // (void**) av;
    if (ac == 2){
        try{
            BitcoinExchange B(av[1]);
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    else
        std::cout << "Error: the programe take exactly 1 argument: a file.txt" << std::endl;   
}