project: main.o mario.o game.o map.o color.o createmap.o menu.o list.o mons.o createmons.o
	cc -Wall main.o mario.o game.o map.o color.o createmap.o menu.o list.o mons.o createmons.o -o project -lncurses -lpthread
main.o: main.c main.h
	cc -c -Wall main.c -lncurses -lpthread
mario.o: mario.c main.h
	cc -c -Wall mario.c -lncurses -lpthread
game.o: game.c main.h
	cc -c -Wall game.c -lncurses -lpthread
map.o: map.c main.h
	cc -c -Wall map.c -lncurses -lpthread
color.o: color.c main.h
	cc -c -Wall color.c -lncurses -lpthread
createmap.o: createmap.c main.h
	cc -c -Wall createmap.c -lncurses -lpthread
menu.o: menu.c main.h
	cc -c -Wall menu.c -lncurses -lpthread
list.o: list.c main.h
	cc -c -Wall list.c -lncurses -lpthread
mons.o: mons.c main.h
	cc -c -Wall mons.c -lncurses -lpthread
createmons.o: createmons.c main.h
	cc -c -Wall createmons.c -lncurses -lpthread
