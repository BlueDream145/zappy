##
## EPITECH PROJECT, 2019
## Lib
## File description:
## Makefile
##

RM		=	rm -f

all:
	$(MAKE) -C openApp irrlicht
	cp openApp/libopenApp.a .

tests_run:
	$(MAKE) -C openApp tests_run

clean:
	$(MAKE) -C openApp clean

fclean:
	$(MAKE) -C openApp fclean
	$(RM) openApp/libopenApp.a

re: fclean all

.PHONY: all clean fclean re