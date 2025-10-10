#include "BitcoinExchange.hpp"

int main()
{
    try{
        BitcoinExchange();
    }
    catch(std::exception& e){
        std::cout << e.what() << std::endl;
    }

}