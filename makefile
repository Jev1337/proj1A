prog:main.o gamehead.o
	gcc main.o gamehead.o -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
gamehead.o:gamehead.c
	gcc -c gamehead.c -g
