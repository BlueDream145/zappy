##
## EPITECH PROJECT, 2019
## PSU_zappy_2018
## File description:
## Makefile
##

NAME		=	libgame.a
TESTS		=	run_tests

EXTFLAGS	=
CFLAGS		=	-Wall -Werror -Wextra -fPIC $(EXTFLAGS) -g3
CPPFLAGS	=	-I . -I ../
LDFLAGS		=	-L ../ -llist -lm

FLAGS		=	$(CFLAGS) $(CPPFLAGS) $(LDFLAGS)

SRC			=	core.c \
				core_map.c \
				core_map_look.c \
				core_map_tools.c \
				core_players.c \
				core_sound.c \
				core_player_remove.c \
				map.c \
				map_data.c \
				tile.c \
				tile_objects.c \
				player_handler.c \
				player_handler_players.c \
				player.c \
				player_move.c \
				player_getters.c \
				player_setters.c \
				player_objects.c \
				format_string.c \
				object.c \
				elevation.c \
				resources.c

TSRC		=	Tests/tests_core.c \
				Tests/tests_core_sound_1.c \
				Tests/tests_core_sound_2.c

OBJ			=	$(SRC:.c=.o)
TOBJ		=	$(OBJ) $(TSRC:.c=.o)

CC			=	cc
RM			=	rm -f

all: compile_dependencies $(NAME)
	cp $(NAME) ..

$(NAME): $(OBJ)
	ar -rc $(NAME) $(OBJ)

compile_dependencies:
	$(MAKE) -C ../List

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
