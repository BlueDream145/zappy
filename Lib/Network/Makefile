##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##

NAME		=	libnet.a
TESTS		=	run_tests

EXTFLAGS	=
CFLAGS		=	-Wall -Werror -Wextra -fPIC $(EXTFLAGS)
CPPFLAGS	=	-I .
LDFLAGS		=

FLAGS		=	$(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

SRC			=	socket.c \
				socket_api.c \
				socket_stream.c \
				socket_data.c \
				socket_connexion.c \
				socket_select.c \
				socket_helper.c

TSRC		=	Tests/tests_Socket.cpp \
				Tests/tests_socket.cpp

OBJ			=	$(SRC:.c=.o)
TOBJ		=	$(OBJ) $(TSRC:.cpp=.o)

CC			=	cc
RM			=	rm -f

all: $(NAME)
	cp $(NAME) ..

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

tests_run:
	$(MAKE) compile_tests EXTFLAGS="-lcriterion --coverage -std=c++14 -pthread" CC="g++"
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