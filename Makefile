NAME = dogle

# SRC = 	anton-triangle.cpp \

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
		src/EngineClass/Start.cpp \
		src/EngineClass/Physics.cpp \
		src/EngineClass/Inputs.cpp \
		src/EngineClass/GameLogic.cpp \
		src/EngineClass/Render.cpp \
		src/EngineClass/Gui.cpp \
		src/EngineClass/Pause.cpp \
		src/EngineClass/Destroy.cpp \
		src/EngineClass/Stop.cpp \

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
			$(HOME)/.brew/Cellar/assimp/3.1.1/lib/libassimp.dylib\

FLAGS = -Wall -Wextra -Werror -std=c++14

CC = clang++ 

SOIL2 = include/soil2/lib/macosx/libsoil2-debug.a

all: $(NAME)

$(NAME): $(SOIL2) $(OBJ)
	$(CC) $(FLAGS) $(INCLUDES) $(LIBRARIES) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

$(SOIL2):
	make -C include/soil2/make/macosx soil2-static-lib

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean 
	make -j -j -j
