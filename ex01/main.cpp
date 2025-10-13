#include "RPN.hpp"


int main (int ac, char **av){
    if (ac ==  2){
        const std::string a(av[1]);
        try{
            RPN s(a);
        }
        catch(std::exception& e){
            std::cerr << e.what() << std::endl;
        }
    }
    else{
        std::cout << "The Programe Must take Exactly One Argument." << std::endl;
    }
}
