all: castelo

castelo: castelo.c
	gcc -lGL -lGLU -lglut castelo.c -o castelo

.PHONY: clean mrproper

clear: 
	rm -f castelo

mrproper: clear
	rm  -f castelo