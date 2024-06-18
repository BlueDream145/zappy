##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##

NAME		=	graphical
TESTS		=	run_tests

EXTFLAGS	=
CXXFLAGS	=	-Wall -Werror -Wextra -std=c++17 $(EXTFLAGS)
CPPFLAGS	=	-I . -I ../Lib -I ../Extern/openApp/Includes
LDFLAGS		=	-L ../Lib -lnet -L ../Extern -lopenApp -lIrrlicht -lpthread

FLAGS		=	$(CXXFLAGS) $(CPPFLAGS) $(LDFLAGS)

MAIN		=	main.cpp

SRC			=	GameScreen.cpp

TSRC		=	Tests/tests_Graphical.cpp

OBJ			=	$(SRC:.cpp=.o)
TOBJ		=	$(OBJ) $(TSRC:.cpp=.o)

CC			=	g++
RM			=	rm -f

all: compile_dependencies $(NAME)
	cp $(NAME) ..

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(MAIN) $(OBJ) $(FLAGS)

compile_dependencies:
	$(MAKE) -C ../Lib/Network
	$(MAKE) -C ../Extern

tests_run: compile_dependencies
	$(MAKE) compile_tests EXTFLAGS="-lcriterion --coverage"
	./$(TESTS)

coverage: tests_run
	gcovr --exclude Tests .

compile_tests: $(TOBJ)
	$(CC) -o $(TESTS) $(TOBJ) $(FLAGS)

clean:
	$(RM) $(OBJ)
	$(RM) $(TOBJ)
	find . -type f -name 'vgcore.*' -delete
	find . -type f -name '*.gcno' -delete
	find . -type f -name '*.gcda' -delete

fclean: clean
	$(RM) $(NAME)
	$(RM) $(TESTS)

re: fclean all

.PHONY: all tests_run coverage compile_tests clean fclean re