NAME = theta_finder
SRCS = *.cpp
FLAGS = -Wall -Wextra -Werror
OBJ = $(SRCS:.cpp=.o)

name:	$(OBJ)
		g++ $(FLAGS) $(SRCS) -o $(NAME) -I./../sdl2/include/SDL2/SDL -I./../sdl2/include/SDL2/SDL_types -lSDL2

all:	$(NAME)

clean:
		rm -rf $(OBJ)

fclean:	clean
		rm -rf $(NAME) thetas.csv

re:		fclean all