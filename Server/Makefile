##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##

NAME		=	zappy_server
TESTS		=	run_tests

EXTFLAGS	=
CFLAGS		=	-I ./inc -Wall -Werror -Wextra -fPIC -g3 $(EXTFLAGS)
CPPFLAGS	=	-I . -I ../Lib
LDFLAGS		=	-L ../Lib -l list -lnet -lgame -lm

FLAGS		=	$(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

MAIN		=	src/main.c

SRC			=	src/handle_client.c	\
				src/zappy_server.c	\
				src/protocol.c		\
				src/signal.c		\
				src/update.c		\
				src/update_data.c	\
				src/utils.c			\
				src/ai_commands.c	\
				src/init_server.c	\
				src/client_auth.c	\
				src/action_cmd.c	\
				src/info_cmd.c		\
				src/check_args.c

TSRC		=	Tests/tests_server.c

OBJ			=	$(SRC:.c=.o)
TOBJ		=	$(OBJ) $(TSRC:.c=.o)

CC			=	cc
RM			=	rm -f

all: compile_dependencies $(NAME)
	cp $(NAME) ..

$(NAME): $(OBJ)
	$(CC) -o $(NAME) $(MAIN) $(OBJ) $(FLAGS)

compile_dependencies:
	$(MAKE) -C ../Lib/Network
	$(MAKE) -C ../Lib/Game
	$(MAKE) -C ../Lib/List

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