##
## EPITECH PROJECT, 2024
## libncurse
## File description:
## Makefile
##

SRC = $(wildcard *.cpp) \
	$(wildcard source/Window/*.cpp) \
	$(wildcard source/Pixel/*.cpp) \
	$(wildcard source/Signal/*.cpp) \
	$(wildcard source/Input/*.cpp) \
	$(wildcard window/*.cpp) \
	$(wildcard logger/*.cpp) \
	$(wildcard testing/*.cpp) \
	$(wildcard include/Window/*.cpp)

OBJ = $(SRC:.cpp=.o)

NAME = libncurse

CXX = g++

CXXFLAGS = -Wall -Wextra -lpng -I include/

all: $(NAME)

$(NAME): $(OBJ)
	$(CXX) -o $(NAME) $(OBJ) $(CXXFLAGS) 

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all