prog:main.o enigme2.o minimap.o background.o es.o enigme.o character.o gamehead.o ninjahubstd.o init.o affichage.o timer.o
	gcc main.o enigme2.c minimap.c background.c es.c enigme.c character.c gamehead.o ninjahubstd.o init.o affichage.o timer.o -o prog -lSDL -lSDL_ttf -g -lSDL_image -lSDL_mixer
main.o:main.c
	gcc -c main.c -g
init.o:init.c
	gcc -c init.c -g
affichage.o:affichage.c
	gcc -c affichage.c -g
ninjahubstd.o:ninjahubstd.c
	gcc -c ninjahubstd.c -g
gamehead.o:gamehead.c
	gcc -c gamehead.c -g
timer.o:timer.c
	gcc -c timer.c -g
character.o:character.c
	gcc -c character.c -g
enigme.o:enigme.c
	gcc -c enigme.c -g
es.o:es.c
	gcc -c es.c -g
background.o:background.c
	gcc -c background.c -g
minimap.o:minimap.c
	gcc -c minimap.c -g
enigme2.o:enigme2.c
	gcc -c enigme2.c -g

