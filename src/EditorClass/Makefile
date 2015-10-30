# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: brehaili <brehaili@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/20 13:38:52 by brehaili          #+#    #+#              #
#    Updated: 2015/04/20 13:38:55 by brehaili         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = editor

SRC = 	UI.cpp \
		Popup.cpp \
		myColumn.cpp \
		ToggleColumn.cpp

SRC +=	../CoreClass/Application.cpp \
		../CoreClass/Scene.cpp \
		../CoreClass/GameObject.cpp \
		../CoreClass/Transform.cpp \
		../CoreClass/Skin.cpp \
		../CoreClass/Camera.cpp \
		../CoreClass/Light.cpp \
		../CoreClass/Script.cpp \

SRC +=	../EngineClass/Engine.cpp \
		../EngineClass/StateMachine.cpp \
		../EngineClass/Start.cpp \
		../EngineClass/Physics.cpp \
		../EngineClass/Inputs.cpp \
		../EngineClass/GameLogic.cpp \
		../EngineClass/Render.cpp \
		../EngineClass/Gui.cpp \
		../EngineClass/Pause.cpp \
		../EngineClass/Destroy.cpp \
		../EngineClass/Stop.cpp \

SRC +=	../BuilderClass/Builder.cpp \
		../BuilderClass/ScriptFactory.cpp \

INCLUDE = 	-I$(HOME)/.brew/include\
			-I ../../include \
			-I ../../src/CoreClass \
			-I ../../src/EngineClass \
			-I ../../src/BuilderClass \
			-I ../../src/UtilsClass \
			-I ../../src/EditorClass \
			-I ../../resources/Scripts \
			-I ../../$(HOME)/.brew/include \
			-I ../../include/soil2/src/SOIL2 \
			`pkg-config --cflags gtkmm-3.0` \

GAMESCRIPTS = ../../resources/Scripts/GameScripts.a

LIBRARIES =	-L$(HOME)/.brew/lib -lglfw3\
			-L$(HOME)/.brew/lib/ -lGLEW\
			-L../../include/soil2/lib/macosx/ -lsoil2-debug\
			-framework OpenGL\
			-framework Cocoa\
			-framework IOKit\
			-framework CoreVideo \
			$(HOME)/.brew/Cellar/assimp/3.1.1/lib/libassimp.dylib\
			../../resources/Scripts/GameScripts.a \
			`pkg-config --libs gtkmm-3.0` \

SOIL2 = ../../include/soil2/lib/macosx/libsoil2-debug.a

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -lGlew 

all: $(NAME)

$(NAME): $(SOIL2) $(GAMESCRIPTS) $(SRC:.c=.o)
	g++ -std=c++14 -o $@ $^ -Wall -Wextra -Werror ${INCLUDE} ${LIBRARIES}
	mv $(NAME) ../../

$(GAMESCRIPTS):
	make -C ../../resources/Scripts/

$(SOIL2):
	make -C ../../include/soil2/make/macosx soil2-static-lib

%.o: %.cpp
	g++ -c $^ -o $@ -Wall -Wextra -Werror -g ${INCLUDE}

clean:
	rm -rf *.o

fclean: clean
	rm -rf ../../$(NAME)

re: fclean all
