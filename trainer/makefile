NAME=trainer
SRCS=*.cpp
FLAGS=-Wall -Wextra -Werror
OBJ=(SRCS.c:.o)

name:
	g++ $(FLAGS) $(SRCS) -o $(NAME)

clean:
	rm -rf $(NAME)

fclean: clean
	rm -rf .o

all:
	$(NAME)

re:	fclean all