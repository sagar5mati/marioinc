/* marioinc -- an implemetation of mario in c
   Copyright sagarpanchmatia@outlook.com Sagar Panchmatia

   This program is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program.  If not, see <http://www.gnu.org/licenses/>.  */
#include "main.h"
//Draw menu on screen
void drawmenu(menu *m) {
	int c, y, x;
	getmaxyx(stdscr, y, x);
	attron(COLOR_PAIR(WHITE_BLUE));
	for(c = 0; c < m->size; c++) {		
		if(c == m->hlight)
			attron(A_BOLD);
		mvaddstr(y / 2 - 7 + c * 2, x / 2 - 5, m->entry[c]);
		attroff(A_BOLD);
	}
	attroff(COLOR_PAIR(WHITE_BLUE));
	refresh();
}
//Code for moving around the menu
gameinfo initmenu(game *g) {
	gameinfo r;
	initgameinfo(&r);	
	menu init;
	int i, key, level = 1, stage = 1;
	char *name;
	init.size = 4;
	init.hlight = 0;
	init.entry = (char **)malloc(sizeof(char *) * init.size);
	for(i = 0; i < init.size; i++) {
		init.entry[i] = (char *)malloc(sizeof(char) * 21);
		init.entry[i] = "\0";
	}
	init.entry[0] = " NEW GAME";
	init.entry[1] = "LOAD GAME";
	init.entry[2] = "  HELP";
	init.entry[3] = "  EXIT";
	wattron(stdscr, COLOR_PAIR(WHITE_BLUE));
	for(i = 0; i < g->cols; i++) {
		mvaddch(1, i, ' ');
		mvaddch(2, i, ' ');
	}
	wattroff(stdscr, COLOR_PAIR(WHITE_BLUE));
	attron(COLOR_PAIR(WHITE_BLUE));
	mvwprintw(stdscr, 1, 5, "LEVEL %d", level);
	mvwprintw(stdscr, 1, g->cols - 12, "STAGE %d", stage);
	attroff(COLOR_PAIR(WHITE_BLUE));
	drawmenu(&init);
	refresh();	
	do {
		key = getch();
		switch(key) {
			case KEY_DOWN:
				init.hlight++;
				if(init.hlight > init.size - 1)
					init.hlight = 0;
				break;
			case KEY_UP:
				init.hlight--;
				if(init.hlight < 0)
					init.hlight = init.size - 1;
				break;
			case KEY_RIGHT:
				if(stage != 3)
					stage++;
				else {
					level++;
					stage = 1;
				}
				break;
			case KEY_LEFT:
				if(stage == 1 && level == 1)
					break;
				if(stage != 1)
					stage--;
				else {
					level--;
					stage = 3;
				}
				break;
			default:
				break;
		}
		attron(COLOR_PAIR(WHITE_BLUE));
		mvwprintw(stdscr, 1, 5, "LEVEL %d", level);
		mvwprintw(stdscr, 1, g->cols - 12, "STAGE %d", stage);
		attroff(COLOR_PAIR(WHITE_BLUE));
		refresh();
		drawmenu(&init);
	} while(key != '\n');
	name = getfilename(level, stage);
	switch(init.hlight) {
		case 0:
			strcpy(r.name, name);
			r.menu = 0;
			break;
		case 1:
			strcpy(r.name, "level0-1");
			r.menu = 2;
			break;
		case 2:
			strcpy(r.name, "level0-1");
			r.menu = 3;
			break;
		case 3:
		default:
			r.menu = -1;
			break;	
	}
	attron(COLOR_PAIR(WHITE_BLUE));
	for(i = 0; i < g->cols; i++) {
		mvaddch(1, i, ' ');
		mvaddch(2, i, ' ');
	}
	attron(COLOR_PAIR(WHITE_BLUE));
	return r;
}
//Code for moving around the menu
gameinfo pausemenu(game *g) {
	gameinfo r;
	initgameinfo(&r);	
	menu pause;
	int i, key;
	pause.size = 4;
	pause.hlight = 0;
	pause.entry = (char **)malloc(sizeof(char *) * pause.size);
	for(i = 0; i < pause.size; i++) {
		pause.entry[i] = (char *)malloc(sizeof(char) * 21);
		pause.entry[i] = "\0";
	}
	pause.entry[0] = " RESUME";
	pause.entry[1] = "SAVE GAME";
	pause.entry[2] = "  HOME";
	pause.entry[3] = "  EXIT";
	drawmenu(&pause);
	do {
		key = getch();
		switch(key) {
			case KEY_DOWN:
				pause.hlight++;
				if(pause.hlight > pause.size - 1)
					pause.hlight = 0;
				break;
			case KEY_UP:
				pause.hlight--;
				if(pause.hlight < 0)
					pause.hlight = pause.size - 1;
				break;			
			default:
				break;
		}
		drawmenu(&pause);
	} while(key != '\n');
	switch(pause.hlight) {
		case 0: 
			break;
		case 1:
			savegame(g);
			break;		
		case 2:
			g->exit = 1;
			break;
		case 3:
			g->exit = 1;
			r.menu = -1;
		default:
			break;
	}	
	return r;
}
//Build filename to be loaded
char *getfilename(int level, int stage) {
	char *name = (char *)malloc(sizeof(char) * 100);
	name[0] = 'l';
	name[1] = 'e';
	name[2] = 'v';
	name[3] = 'e';
	name[4] = 'l';
	name[5] = level + 48;	
	name[6] = '-';
	name[7] = stage + 48;
	name[8] = '\0';
	return name;
}
//Code for moving around the menu
gameinfo loadmenu(game *g) {
	gameinfo r;
	initgameinfo(&r);
	menu load;
	int i, key;
	char *name;
	list *t = &g->game;
	node *temp = t->head;
	wattron(stdscr, COLOR_PAIR(WHITE_BLUE));
	for(i = 0; i < g->cols; i++) {
		mvaddch(1, i, ' ');
		mvaddch(2, i, ' ');
	}
	wattroff(stdscr, COLOR_PAIR(WHITE_BLUE));
	if(!t->count) {
		attron(COLOR_PAIR(WHITE_BLUE));
		mvwaddstr(stdscr, g->rows / 2, g->cols / 2 - 10, "Sorry, no saved games yet!");
		refresh();
		napms(1000);
		attroff(COLOR_PAIR(WHITE_BLUE));
		return r;
	}
	load.size = t->count + 1;
	load.hlight = 0;
	load.entry = (char **)malloc(sizeof(char *) * load.size);
	for(i = 0; i < load.size; i++) {
		load.entry[i] = (char *)malloc(sizeof(char) * 21);
		strcpy(load.entry[i], "\0");
	}
	for(i = 0; i < load.size - 1; i++) {
		load.entry[i] = temp->name;
		temp = temp->next;
	}
	load.entry[load.size - 1] = "BACK";
	drawmenu(&load);
	do {
		key = getch();
		switch(key) {
			case KEY_DOWN:
				load.hlight++;
				if(load.hlight > load.size - 1)
					load.hlight = 0;
				break;
			case KEY_UP:
				load.hlight--;
				if(load.hlight < 0)
					load.hlight = load.size - 1;
				break;			
			default:
				break;
		}
		drawmenu(&load);
	} while(key != '\n');
	for(i = 0; i < load.size - 1; i++) {
		if(load.hlight == i) {
			name = viewl(t, i + 1);
			strcpy(r.name, name);
			r.menu = 0;
			break;
		}			
	}
	return r;
}
//Code for moving around the menu
gameinfo helpmenu(game *g) {
	FILE *fp;
	char ch;	
	gameinfo r;
	initgameinfo(&r);
	clear();
	bkgd(COLOR_PAIR(WHITE_BLUE));
	fp = fopen("help.txt", "r");
	while((ch = fgetc(fp)) != EOF)
		addch(ch);
	fclose(fp);
	nodelay(stdscr, FALSE);
	getch();
	nodelay(stdscr, TRUE);
	return r;
}
