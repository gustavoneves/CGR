all: Neve

Neve: neve.c
	gcc -lGL -lGLU -lm -lglut neve.c -o neve
	
.PHONY: clean mrproper

clear: 
	rm -f neve

mrproper: clear
	rm  -f neve