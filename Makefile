NAME = dogle

SRC = 	src/CoreClass/main.cpp \
		src/CoreClass/Application.cpp \
		src/CoreClass/Scene.cpp \
		src/CoreClass/GameObject.cpp \
		src/CoreClass/Transform.cpp \
		src/CoreClass/Skin.cpp \
		src/CoreClass/Camera.cpp \
		src/CoreClass/Light.cpp \
		src/CoreClass/Script.cpp \
		src/CoreClass/Collider.cpp \

SRC +=	src/BuilderClass/ScriptFactory.cpp \
		src/BuilderClass/Builder.cpp \
		src/BuilderClass/ScriptManager.cpp \

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

GAMESCRIPTS = resources/Scripts/GameScripts.a

OBJ = 	$(SRC:.cpp=.o)

INCLUDES = 	-Iinclude \
			-Iresources/Scripts \
			-Isrc/CoreClass \
			-Isrc/EngineClass \
			-Isrc/BuilderClass \
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
			-framework IOKit\
			-framework CoreVideo \
			$(HOME)/.brew/Cellar/assimp/3.1.1/lib/libassimp.dylib\
			resources/Scripts/GameScripts.a \
			-L$(HOME)/.brew/lib -lBullet3Common -lBullet3Dynamics\
			-lBullet3Dynamics\
			-lBulletCollision\
			-lBullet3Collision\
			-lBullet3Geometry\
			-lBulletDynamics\
			-lBullet3Common\
			-lBullet3OpenCL_clew\
			-lBulletSoftBody\
			-lLinearMath\

DEPRECATED = -Wno-ignored-qualifiers -Wno-deprecated-register

FLAGS =  -Wall -Wextra -Werror -std=c++14 -g $(DEPRECATED)

CC = clang++ 

SOIL2 = include/soil2/lib/macosx/libsoil2-debug.a

BULLET_INC = -I$(HOME)/.brew/include/bullet


all: $(NAME)

COMPGAMESCRIPTS:
	make -C resources/Scripts/

$(NAME): COMPGAMESCRIPTS $(SOIL2) $(OBJ) 
	$(CC) $(FLAGS) $(INCLUDES) $(LIBRARIES) $(OBJ) -o $(NAME)

%.o: %.cpp
	$(CC) -c $(FLAGS) $(INCLUDES) $(BULLET_INC) $< -o $@

$(SOIL2):
	make -C include/soil2/make/macosx soil2-static-lib

editor:
	make -C src/EditorClass/

editor_re:
	make -C src/EditorClass/ re

editor_fclean:
	make -C src/EditorClass/ fclean

clean:
	rm -f $(OBJ)
	make -C resources/Scripts/ clean


fclean: clean
	rm -f $(NAME)
	rm -rf $(NAME).dSYM
	make -C resources/Scripts/ fclean

re: fclean
	make -j -j -j
