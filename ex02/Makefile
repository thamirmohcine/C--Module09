NAME=PmergeMe

CC= c++ 

CPPFLAGS= -std=c++98 -Wall -Wextra -Werror

SRC= main.cpp PmergeMe.cpp

OBJ= main.o PmergeMe.o

HEADER= PmergeMe.hpp

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(CPPFLAGS) $(OBJ) -o $(NAME)

%.o: %.cpp $(HEADER)
	$(CC) $(CPPFLAGS) $< -c -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf $(NAME)

re: fclean all