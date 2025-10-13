#include "BitcoinExchange.hpp"

int main(int ac, char **av)
{
    if (ac == 2){
        const std::string s(av[1]);
        try{
            BitcoinExchange B(s);
        }
        catch(std::exception& e){
            std::cout << e.what() << std::endl;
        }
    }
    else
        std::cout << "Error: the programe take exactly 1 argument: a file.txt" << std::endl;   
}