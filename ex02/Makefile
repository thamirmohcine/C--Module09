NAME=RPN

CC= c++ 

CPPFLAGS= -Wall -Wextra -Werror -fsanitize=address -g3

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