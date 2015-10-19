NAME = Editor

SRC =	src/main.cpp \
		src/WindowClass.cpp

OBJ = $(SRC:.cpp=.o)

FLAGS = -std=c++11

INCLUDES = 	`pkg-config --cflags gtkmm-2.4`
			
LIBRARIES = `pkg-config --libs gtkmm-2.4`

all: $(NAME)

$(NAME): $(OBJ)
	clang++ $(FLAGS) $(INCLUDES) $(LIBRARIES) $(OBJ) -o $(NAME)

%.o: %.cpp
	clang++ -c $(FLAGS) $(INCLUDES) $< -o $@

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)

re: fclean all
