##
## EPITECH PROJECT, 2019
## Lib
## File description:
## Makefile
##

all:
	$(MAKE) -C List
	$(MAKE) -C Network
	$(MAKE) -C Game

tests_run:
	$(MAKE) -C List tests_run
	$(MAKE) -C Game tests_run
	$(MAKE) -C Network tests_run

clean:
	$(MAKE) -C List clean
	$(MAKE) -C Game clean
	$(MAKE) -C Network clean

fclean:
	$(MAKE) -C List fclean
	$(MAKE) -C Game fclean
	$(MAKE) -C Network fclean
	rm -f lib*.a

re: fclean all

.PHONY: all clean fclean re