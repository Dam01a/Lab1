# list/Makefile
#
# Makefile for list implementation and test file.
#
# Damola
# damola.quadri@bison.howard.edu

list: list.c list.h main.c
	gcc -o list main.c list.c list.h

   