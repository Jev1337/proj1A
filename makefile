prog:main.o gamehead.o ninjahubstd.o
	gcc main.o gamehead.o ninjahubstd.o -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
ninjahubstd.o:ninjahubstd.c
	gcc -c ninjahubstd.c -g
gamehead.o:gamehead.c
	gcc -c gamehead.c -g