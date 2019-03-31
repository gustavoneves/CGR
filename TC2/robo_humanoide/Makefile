all: robo_humanoide

robo_humanoide:
	gcc -lGL -lGLU -lglut robo_humanoide.c -o robo_humanoide

.PHONY: clean mrproper

clear: 
	rm -f robo_humanoide

mrproper: clear
	rm  -f robo_humanoide