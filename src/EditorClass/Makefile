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

NAME = unity_scop
SRC = UI.cpp

INCLUDE = -I$(HOME)/.brew/include\
			`pkg-config --cflags gtkmm-3.0`

LIBRARIES =	-L$(HOME)/.brew/lib -lglfw3\
			-L$(HOME)/.brew/lib/ -lGLEW\
			`pkg-config --libs gtkmm-3.0`

FRAMEWORKS = -framework Cocoa -framework OpenGL -framework IOKit -lGlew 

all: $(NAME)

$(NAME): $(SRC:.c=.o)
	g++ -std=c++11 -o $@ $^ -Wall -Wextra -Werror ${INCLUDE} ${LIBRARIES}

%.o: %.cpp
	g++ -c $^ -o $@ -Wall -Wextra -Werror -g ${INCLUDE}

clean:
	rm -rf $(SRC:.c=.o)

fclean: clean
	rm -rf $(NAME)

re: fclean all
