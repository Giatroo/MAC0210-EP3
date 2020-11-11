CC = gcc
FLAGS = -O0 -Wall

all : parte1 parte2
	@echo "Compilado corretamente"

parte1 : parte1.o
	${CC} $^ ${FLAGS} -o $@

parte2 : parte2.o
	${CC} $^ ${FLAGS} -o $@ -lm
