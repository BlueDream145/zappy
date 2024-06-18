##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##

NAME		=	liblist.a
TESTS		=	run_tests

EXTFLAGS	=
CFLAGS		=	-Wall -Werror -Wextra -fPIC $(EXTFLAGS)
CPPFLAGS	=	-I .
LDFLAGS		=

FLAGS		=	$(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

SRC			=	list.c \
				list_add.c \
				list_remove.c

TSRC		=	Tests/tests_list.c

OBJ			=	$(SRC:.c=.o)
TOBJ		=	$(OBJ) $(TSRC:.c=.o)

CC			=	cc
RM			=	rm -f

all: $(NAME)
	cp $(NAME) ..

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

tests_run:
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