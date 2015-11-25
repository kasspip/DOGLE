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

FLAGS = -Wall -Wextra -Werror -std=c++14

CC = clang++ 

all: $(NAME)

$(NAME): $(OBJ)
	@ar rc $(NAME) $(OBJ)
	@ranlib $(NAME)

%.o: %.cpp
	$(CC) -c $(FLAGS) $(INCLUDES) $<

clean:
	rm -f $(OBJ)
	rm -f *.o

fclean: clean
	rm -f $(NAME)

re: fclean all
