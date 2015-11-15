MARIO IN C
Sagar Panchmatia 111403067

NOTE:
The bug seen in loading a game in the video has been solved

Description:

The following program is an implementation of the classic Mario game in C Language using ncurses library
To implement this game I divided the game into three different parts: map, player(mario), monsters

Map:
I created the map as a different data structure and stored all the information like the positions of components
of the map, their different states, size, color in it.
Each component like bricks and pipes has its function like printing itself on the screen

Mario:
The data structure for mario holds information like its position its state, life.
This data structure has functions ehich help it print on the screen move according to the user input

Monster:
It reads from a file so that it can change for different maps
It also had fuctions that help it move and collide wit mario

Game:
Game is a data structure which holds the above data structures and other general information about the game

Menu:
This data structure holds information about the dierent menus displayed during the game

When the game is initially started it fills the game structure with a preliminary map and menu
As the progresses different structures are loaded in the game structure
The actual is a multithreaded program in which both of the threads run an infinite while loop one of each takes user input 
and makes the player move and the other thread makes the monsters move
