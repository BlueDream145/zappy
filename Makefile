##
## EPITECH PROJECT, 2019
## Lib
## File description:
## Makefile
##

RM		=	rm -f

all:
	$(MAKE) -C Lib
	$(MAKE) -C Server
	$(MAKE) -C AI
	$(MAKE) -C Graphical

tests_run:
	$(MAKE) -C Lib tests_run
	$(MAKE) -C Server tests_run
	$(MAKE) -C AI tests_run
	$(MAKE) -C Graphical tests_run
	$(MAKE) -C Extern tests_run

clean:
	$(MAKE) -C Lib clean
	$(MAKE) -C Server clean
	$(MAKE) -C AI clean
	$(MAKE) -C Graphical clean
	$(MAKE) -C Extern clean

fclean:
	$(MAKE) -C Lib fclean
	$(MAKE) -C Server fclean
	$(MAKE) -C AI fclean
	$(MAKE) -C Graphical fclean
	$(MAKE) -C Extern fclean
	$(RM) zappy_ai zappy_server graphical

re: fclean all

.PHONY: all clean fclean re