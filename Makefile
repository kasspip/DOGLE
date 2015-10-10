NAME = gogle

SRC = 	src/CoreClass/main.cpp \
		src/CoreClass/Application.cpp \
		src/CoreClass/Scene.cpp \
		src/CoreClass/GameObject.cpp \
		src/CoreClass/Transform.cpp \
		src/CoreClass/Skin.cpp \
		src/CoreClass/Camera.cpp \
		src/CoreClass/Light.cpp \
		src/UtilsClass/RGB.cpp \


OBJ = $(SRC:.cpp=.o)

INCLUDES = 	-Iinclude \
			-Isrc/CoreClass \
			-Isrc/UtilsClass \
			-Isrc/EditorClass \
			-Isrc/EngineClass \

LIBRARIES =	 -g

FLAGS = -Wall -Wextra -Werror

CC = clang++ 

all: $(NAME)

$(NAME): $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(LIBRARIES) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean all
