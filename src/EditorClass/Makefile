# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: cobrecht <cobrecht@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2015/04/20 13:38:52 by brehaili          #+#    #+#              #
#    Updated: 2015/10/31 11:43:10 by cobrecht         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = editor

SRC = 	UI.cpp \
		Popup.cpp \
		myColumn.cpp \
		ToggleColumn.cpp \
		PopupInstancePrefab.cpp \
		PopupSelectItems.cpp \
		PopupConfirmation.cpp \

SRC +=	../CoreClass/Application.cpp \
		../CoreClass/Scene.cpp \
		../CoreClass/GameObject.cpp \
		../CoreClass/Transform.cpp \
		../CoreClass/Skin.cpp \
		../CoreClass/Camera.cpp \
		../CoreClass/Light.cpp \
		../CoreClass/Script.cpp \
		../CoreClass/Collider.cpp \
		../CoreClass/Text.cpp \


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
		../BuilderClass/ScriptManager.cpp \

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
			-I$(HOME)/.brew/include/bullet \
			-I$(HOME)/.brew/Cellar/gtkmm3/3.18.0/include/gtkmm-3.0 \
			-I$(HOME)/.brew/Cellar/gtkmm3/3.18.0/lib/gtkmm-3.0/include \
			-I$(HOME)/.brew/Cellar/atkmm/2.24.1/include/atkmm-1.6 \
			-I$(HOME)/.brew/Cellar/gtk+3/3.18.5/include/gtk-3.0/unix-print \
			-I$(HOME)/.brew/Cellar/gtkmm3/3.18.0/include/gdkmm-3.0 \
			-I$(HOME)/.brew/Cellar/gtkmm3/3.18.0/lib/gdkmm-3.0/include \
			-I$(HOME)/.brew/Cellar/glibmm/2.46.2/include/giomm-2.4 \
			-I$(HOME)/.brew/Cellar/glibmm/2.46.2/lib/giomm-2.4/include \
			-I$(HOME)/.brew/Cellar/pangomm/2.38.1/include/pangomm-1.4 \
			-I$(HOME)/.brew/Cellar/pangomm/2.38.1/lib/pangomm-1.4/include \
			-I$(HOME)/.brew/Cellar/glibmm/2.46.2/include/glibmm-2.4 \
			-I$(HOME)/.brew/Cellar/glibmm/2.46.2/lib/glibmm-2.4/include \
			-I$(HOME)/.brew/Cellar/gtk+3/3.18.5/include/gtk-3.0 \
			-I$(HOME)/.brew/Cellar/glib/2.46.2/include/gio-unix-2.0/ \
			-I$(HOME)/.brew/Cellar/cairo/1.14.4/include/cairo \
			-I$(HOME)/.brew/Cellar/libepoxy/1.3.1/include \
			-I$(HOME)/.brew/Cellar/pango/1.38.1/include/pango-1.0 \
			-I$(HOME)/.brew/Cellar/harfbuzz/1.0.4/include/harfbuzz \
			-I$(HOME)/.brew/Cellar/pango/1.38.1/include/pango-1.0 \
			-I$(HOME)/.brew/Cellar/atk/2.18.0/include/atk-1.0 \
			-I$(HOME)/.brew/Cellar/cairo/1.14.4/include/cairo \
			-I$(HOME)/.brew/Cellar/cairomm/1.12.0/include/cairomm-1.0 \
			-I$(HOME)/.brew/Cellar/cairomm/1.12.0/lib/cairomm-1.0/include \
			-I$(HOME)/.brew/Cellar/cairo/1.14.4/include/cairo \
			-I$(HOME)/.brew/Cellar/pixman/0.32.8/include/pixman-1 \
			-I$(HOME)/.brew/Cellar/fontconfig/2.11.1/include \
			-I$(HOME)/.brew/Cellar/freetype/2.6_1/include/freetype2 \
			-I$(HOME)/.brew/Cellar/libpng/1.6.19/include/libpng16 \
			-I$(HOME)/.brew/Cellar/libsigc++/2.6.2/include/sigc++-2.0 \
			-I$(HOME)/.brew/Cellar/libsigc++/2.6.2/lib/sigc++-2.0/include \
			-I$(HOME)/.brew/Cellar/gdk-pixbuf/2.32.2/include/gdk-pixbuf-2.0 \
			-I$(HOME)/.brew/Cellar/libpng/1.6.19/include/libpng16 \
			-I$(HOME)/.brew/Cellar/glib/2.46.2/include/glib-2.0 \
			-I$(HOME)/.brew/Cellar/glib/2.46.2/lib/glib-2.0/include \
			-I$(HOME)/.brew/opt/gettext/include \
			-I$(HOME)/.brew/include/freetype2 \
			
GAMESCRIPTS = ../../resources/Scripts/GameScripts.a

LIBRARIES =	-L$(HOME)/.brew/lib -lglfw3 \
			-L$(HOME)/.brew/lib/ -lGLEW \
			-L../../include/soil2/lib/macosx/ -lsoil2-debug \
			-framework OpenGL \
			-framework Cocoa \
			-framework IOKit \
			-framework CoreVideo \
			$(HOME)/.brew/Cellar/assimp/3.1.1/lib/libassimp.dylib \
			../../resources/Scripts/GameScripts.a \
			-L$(HOME)/.brew/lib -lBullet3Common -lBullet3Dynamics \
			-lBullet3Dynamics \
			-lBulletCollision \
			-lBullet3Collision \
			-lBullet3Geometry \
			-lBulletDynamics \
			-lBullet3Common \
			-lBullet3OpenCL_clew \
			-lBulletSoftBody \
			-lLinearMath \
			-L$(HOME)/.brew/lib/ -lfreetype\
			-L$(HOME)/.brew/Cellar/gtkmm3/3.18.0/lib \
			-L$(HOME)/.brew/Cellar/atkmm/2.24.1/lib \
			-L$(HOME)/.brew/Cellar/gtkmm3/3.18.0/lib \
			-L$(HOME)/.brew/Cellar/glibmm/2.46.2/lib \
			-L$(HOME)/.brew/Cellar/pangomm/2.38.1/lib \
			-L$(HOME)/.brew/Cellar/glibmm/2.46.2/lib \
			-L$(HOME)/.brew/Cellar/gtk+3/3.18.5/lib \
			-L$(HOME)/.brew/Cellar/pango/1.38.1/lib \
			-L$(HOME)/.brew/Cellar/atk/2.18.0/lib \
			-L$(HOME)/.brew/Cellar/cairo/1.14.4/lib \
			-L$(HOME)/.brew/Cellar/glib/2.46.2/lib \
			-L$(HOME)/.brew/Cellar/cairomm/1.12.0/lib \
			-L$(HOME)/.brew/Cellar/cairo/1.14.4/lib \
			-L$(HOME)/.brew/Cellar/libsigc++/2.6.2/lib \
			-L$(HOME)/.brew/Cellar/gdk-pixbuf/2.32.2/lib \
			-L$(HOME)/.brew/Cellar/glib/2.46.2/lib \
			-L$(HOME)/.brew/opt/gettext/lib \
			-lgtkmm-3.0 \
			-latkmm-1.6 \
			-lgdkmm-3.0 \
			-lgiomm-2.4 \
			-lpangomm-1.4 \
			-lglibmm-2.4 \
			-lgtk-3 \
			-lgdk-3 \
			-lpangocairo-1.0 \
			-lpango-1.0 \
			-latk-1.0 \
			-lcairo-gobject \
			-lgio-2.0 \
			-lcairomm-1.0 \
			-lcairo \
			-lsigc-2.0 \
			-lgdk_pixbuf-2.0 \
			-lgobject-2.0 \
			-lglib-2.0 \
			-lintl

OBJ = $(SRC:.cpp=.o)

DEPRECATED = -Wno-ignored-qualifiers -Wno-deprecated-register

FLAGS =  -Wall -Wextra -Werror -std=c++14 -g $(DEPRECATED)

SOIL2 = ../../include/soil2/lib/macosx/libsoil2-debug.a

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -lGlew 

all: $(NAME) 

$(NAME): $(GAMESCRIPTS) $(SOIL2) $(OBJ)	
	clang++ $(FLAGS) $(INCLUDE) $(LIBRARIES) $(OBJ)	-o $(NAME)
	mv $(NAME) ../../

$(GAMESCRIPTS):
	make -C ../../resources/Scripts/

$(SOIL2):
	make -C ../../include/soil2/make/macosx soil2-static-lib

%.o: %.cpp
	clang++ -c $(FLAGS) $(INCLUDE) $< -o $@

clean:
	rm -rf $(OBJ)

fclean: clean
	rm -rf ../../$(NAME)

re: fclean
	make -j -j -j
