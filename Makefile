NAME = dogle

# SRC = 	example.cpp

SRC = 	src/CoreClass/main.cpp \
		src/CoreClass/Application.cpp \
		src/CoreClass/Scene.cpp \
		src/CoreClass/GameObject.cpp \
		src/CoreClass/Transform.cpp \
		src/CoreClass/Skin.cpp \
		src/CoreClass/Camera.cpp \
		src/CoreClass/Light.cpp \
		src/CoreClass/Script.cpp \


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

SCRIPTS_PATH = resources/Scripts

OBJ = 	$(SRC:.cpp=.o)

INCLUDES = 	-Iinclude \
			-Iresources/Scripts \
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

$(NAME): $(SOIL2) $(OBJ) GameScript
	$(CC) $(FLAGS) $(INCLUDES) $(LIBRARIES) $(OBJ) $(SCRIPTS_PATH)/*.o -o $(NAME)

%.o: %.cpp
	$(CC) -c $(FLAGS) $(INCLUDES) $< -o $@

GameScript:
	$(CC) -c $(SCRIPTS_PATH)/*.cpp $(INCLUDES)
	@mv *.o  $(SCRIPTS_PATH)

$(SOIL2):
	make -C include/soil2/make/macosx soil2-static-lib

clean:
	rm -f $(OBJ)
	rm -f $(SCRIPTS_PATH)/*.o

fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM

re: fclean
	make -j -j -j