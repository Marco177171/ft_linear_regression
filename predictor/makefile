NAME = predictor
SRCS = *.cpp
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.cpp=.o)

name:	$(OBJ)
		g++ $(FLAGS) $(SRCS) -o $(NAME)

all:	$(NAME)

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME)

re:		fclean all