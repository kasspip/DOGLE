NAME = dogle

SRC = 	src/CoreClass/main.cpp \
		src/CoreClass/Application.cpp \
		src/CoreClass/Scene.cpp \
		src/CoreClass/GameObject.cpp \
		src/CoreClass/Transform.cpp \
		src/CoreClass/Skin.cpp \
		src/CoreClass/Camera.cpp \
		src/CoreClass/Light.cpp \

SRC +=	src/UtilsClass/RGB.cpp \

SRC +=	src/EngineClass/Engine.cpp \
		src/EngineClass/StateMachine.cpp \
		src/EngineClass/Initialisation.cpp \


OBJ = $(SRC:.cpp=.o)

INCLUDES = 	-Iinclude \
			-Isrc/CoreClass \
			-Isrc/EngineClass \
			-Isrc/UtilsClass \
			-Isrc/EditorClass \
			-Isrc/EngineClass \
			-I$(HOME)/.brew/include \
			-Iinclude/soil2/src/SOIL2 \

LIBRARIES =	-L$(HOME)/.brew/lib -lglfw3\
			-L$(HOME)/.brew/lib/ -lGLEW\
			-Linclude/soil2/lib/macosx/ -lsoil2-debug\
			-framework OpenGL\
			-framework Cocoa\

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
