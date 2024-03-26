##
## EPITECH PROJECT, 2024
## libncurse
## File description:
## Makefile
##

SRC = $(wildcard *.cpp) \
	$(wildcard window/*.cpp) \
	$(wildcard texture/*.cpp) \
	$(wildcard shape/*.cpp) \
	$(wildcard input_management/*.cpp) \
	$(wildcard logger/*.cpp) \
	$(wildcard testing/*.cpp) \

OBJ = $(SRC:.cpp=.o)

NAME = libncurse

CXX = g++

CXXFLAGS = -Wall -Wextra -lpng

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all