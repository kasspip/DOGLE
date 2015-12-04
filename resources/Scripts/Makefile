NAME =	GameScripts.a

include makefile_sources

OBJ = 	$(SRC:.cpp=.o)

INCLUDES = 	-I../../include \
			-I../../resources/Scripts \
			-I../../src/CoreClass \
			-I../../src/EngineClass \
			-I../../src/UtilsClass \
			-I../../src/EditorClass \
			-I../../src/EngineClass \
			-I../../include/soil2/src/SOIL2 \
			-I$(HOME)/.brew/include \
			-I$(HOME)/.brew/include/freetype2 \
			
FLAGS = -Wall -Wextra -Werror -std=c++14

CC = clang++ 

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.cpp
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
