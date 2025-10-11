NAME=RPN

CC= c++ 

CPPFLAGS= -std=c++98 -Wall -Wextra -Werror 

SRC= main.cpp RPN.cpp

OBJ= main.o RPN.o

HEADER= RPN.hpp

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