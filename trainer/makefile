NAME = theta_finder
SRCS = *.cpp
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.cpp=.o)

name:	$(OBJ)
		g++ $(FLAGS) $(SRCS) -o $(NAME) -lSDL2 -lSDL2_ttf

all:	$(NAME)

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME) thetas.csv

re:		fclean all