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
pthread_mutex_t lock;
//Initializes gameinfo structure
void initgameinfo(gameinfo *g) {
	g->name = (char *)malloc(sizeof(char) * 21);	
	strcpy(g->name, "level0-1");
	g->menu = 1;
}
//All the screens are loaded from here and the functions return here
gameinfo reporthere(gameinfo i) {
	int j = 0;
	gameinfo r;
	game g;
	initgameinfo(&r);
	initgame(&g);
	loadgame(&g, i.name);
	updatescreen(&g);
	switch(i.menu) {
		case 0:
			while(1) {
				r = startgame(&g);
				j++;
				writelist(&g.game);
				if(!g.p->life)
					break;
				loadgame(&g, r.name);
				g.p->life -= j;
				wclear(stdscr);
				bkgd(COLOR_PAIR(WHITE_BLUE));
				mvprintw(g.rows / 2, g.cols / 2 - 5, "MARIO X %d", g.p->life);
				refresh();
				napms(2000);	
			}
			break;
		case 1:
			r = initmenu(&g);
			break;
		case 2: 
			r = loadmenu(&g);
			break;
		case 3:
			r = helpmenu(&g);
			break;
		default:
			break;
	}
	return r;		
}
//Initializes the game structure
void initgame(game *g) {
	getmaxyx(stdscr, g->rows, g->cols);
	g->score = 0;
	g->coins = 0;
	g->time = 300;
	g->exit = 0;
	initmario(g);
	initmons(g);
	initmap(g);
	initlist(&g->game);
	readlist(&g->game);
	g->state = NULL;
}
//Loads game information from a file
void loadgame(game *g, char *name) {
	FILE *fp;
	fp = fopen(name, "r");	
	readmario(g, fp);
	readmap(g, fp);
	readmons(g, fp);
	fscanf(fp, "%d %d %d %d %d %d ", &g->rows, &g->cols, &g->score, &g->coins, &g->time, &g->exit);
	readgstate(g, fp);
	fclose(fp);
	g->m->pad = newpad(g->m->rows, g->m->cols);
}
//Loads 2-D array from file
void readgstate(game *g, FILE *fp) {
	int i, j;	
	g->state = (char **)malloc(sizeof(char *) * g->m->rows);
	for(i = 0; i < g->m->rows; i++) {
		g->state[i] = (char *)malloc(sizeof(char) * g->m->cols);
	}
	for(i = 0; i < g->m->rows; i++) {
		for(j = 0; j < g->m->cols; j++)
			fscanf(fp, "%c ", &g->state[i][j]); 
	}
}
//The actual game runs here
gameinfo startgame(game *g) {
	int i, input;	
	gameinfo r;
	mario *t = g->p;
	pthread_t movethings_t;
	initgameinfo(&r);
	pthread_mutex_init(&lock, NULL);
	pthread_create(&movethings_t, NULL, movethings, (void *)g);		
	while(1) {
		input = getch();
		pthread_mutex_lock(&lock);
		switch(t->state) {
			case 'a':
				switch(input) {			
					case 'w': 
						i = movemario_small(g, 'w');
						break;
					case 's': 
						i = movemario_small(g, 's');
						break;
					case 'd': 
						i = movemario_small(g, 'd');
						break;
					case 'a': 
						i = movemario_small(g, 'a');
						break;
					case 'q': 
						i = movemario_small(g, 'q');
						break;
					case 'e': 
						i = movemario_small(g, 'e');
						break;
					case 'Q':
						i = movemario_small(g, 'r');
						break;
					case 'E':
						i = movemario_small(g, 't');
						break;
					case 'D': 
						i = movemario_small(g, 'z');
						break;
					case 'A': 
						i = movemario_small(g, 'x');
						break;
					case 'o': 
						r.menu = -1;
						g->exit = 1;
						break;
					case 'p':
						r = pausegame(g);
						break;
					default:  
						break;
				}
				break;
			case 'b':
				switch(input) {			
					case 'd':
					case 'D': 
						i = movemario_small(g, 'x');
						break;
					case 'a':
					case 'A': 
						i = movemario_small(g, 'z');
						break;
					case 'p':
						r = pausegame(g);
						break;
					case 'o': 
						r.menu = -1;
						g->exit = 1;
						break;
					default:  
						break;
				}
				break;
			case 'c':
			case 'e':
				switch(input) {			
					case 'w': 
						i = movemario_big(g, 'w');
						break;
					case 's': 
						i = movemario_big(g, 's');
						break;
					case 'd': 
						i = movemario_big(g, 'd');
						break;
					case 'a': 
						i = movemario_big(g, 'a');
						break;
					case 'q': 
						i = movemario_big(g, 'q');
						break;
					case 'e': 
						i = movemario_big(g, 'e');
						break;
					case 'Q':
						i = movemario_big(g, 'r');
						break;
					case 'E':
						i = movemario_big(g, 't');
						break;
					case 'A': 
						i = movemario_big(g, 'z');
						break;
					case 'D': 
						i = movemario_big(g, 'x');
						break;
					case ' ': 
						if(t->state == 'e') {
							t->b.state = 1;
							t->b.x = t->x + 3;
							t->b.y = t->y + 1;
						}
						flushinp();
						break;
					case 'p':
						r = pausegame(g);
						break;
					case 'o': 
						r.menu = -1;
						g->exit = 1;
						break;
					default:  
						break;
				}
				break;
			case 'd':
			case 'f':
				switch(input) {			
					case 'd':
					case 'D': 
						i = movemario_big(g, 'x');
						break;
					case 'a': 
					case 'A':
						i = movemario_big(g, 'z');
						break;
					case ' ': 
						if(t->state == 'f') {
							t->b.state = 1;
							t->b.x = t->x + 3;
							t->b.y = t->y;
						}
						break;
					case 'p':
						r = pausegame(g);
						break;
					case 'o': 
						r.menu = -1;
						g->exit = 1;
						break;
					default:  
						break;
				}
				break;				
		}
		pitfall(g);
		if(g->p->x == g->m->s[g->m->ns - 1].x + 10) {
			wclear(stdscr);
			bkgd(COLOR_PAIR(WHITE_BLUE));
			mvprintw(g->rows / 2, g->cols / 2 - 5, "YOU WIN");
			refresh();
			napms(2000);
			g->exit = 3;
			g->p->life = 0;
		}	
		if(g->coins == 25) {
			g->p->life++;
			g->coins = 0;
		}
		if(g->time == 0)
			i = 1;
		pthread_mutex_unlock(&lock);	
		if(i) {
			g->exit = 3;
		}
		if(g->exit == 3) {
			pthread_join(movethings_t, NULL);
			if(g->p->life == 0) {
				initgameinfo(&r);
				return r;
			}
			strcpy(r.name, g->m->name);
			r.menu = 0;
			return r;
		}
		updatescreen(g);	
		if(g->exit == 1) {
			g->p->life = 0;
			pthread_kill(movethings_t, SIGSTOP); 
			return r;
		}
	}
}
//Pauses the game the calls pausemenu
gameinfo pausegame(game *g) {
	gameinfo r;
	initgameinfo(&r);
	g->exit = 2;
	r = pausemenu(g);
	if(g->exit == 2)
		g->exit = 0;
	return r;
} 
//Writes the game structure to a file
void savegame(game *g) {
	FILE *fp;
	char *name = (char *)malloc(21);
	mvwaddstr(stdscr, g->rows / 2 + 3, g->cols / 2 - 5, "Enter Name:");
	move(g->rows / 2 + 5, g->cols / 2 - 5);
	echo();
	nodelay(stdscr, FALSE);
	getnstr(name, 21);
	noecho();
	nodelay(stdscr, TRUE);
	fp = fopen(name, "w+");
	writemario(g, fp);
	writemap(g, fp);
	writemons(g, fp);
	fprintf(fp, "%d %d %d %d %d %d ", g->rows, g->cols, g->score, g->coins, g->time, 0);
	writegstate(g, fp);
	fclose(fp);
	insertl(&g->game, g->game.count + 1, name);
}
//Writes the 2-D array to a file
void writegstate(game *g, FILE *fp) {
	int i, j;
	for(i = 0; i < g->m->rows; i++) {
		for(j = 0; j < g->m->cols; j++)
			fprintf(fp, "%c ", g->state[i][j]);
	}
}
//Refreshes the actual screen, from the pad
void updatescreen(game *g) {
	int i;
	wclear(g->m->pad);
	drawmap(g);	
	printmons(g);
	printmario(g);	
	move(1, 0);
	clrtoeol();
	move(2, 0);
	clrtoeol();
	wattron(stdscr, COLOR_PAIR(WHITE_BLUE));
	for(i = 0; i < g->cols; i++) {
		mvaddch(1, i, ' ');
		mvaddch(2, i, ' ');
	}
	mvwaddstr(stdscr, 1, 3, "SCORE");
	mvwaddstr(stdscr, 1, g->cols / 2 - 2, "TIME");
	mvwaddstr(stdscr, 1, g->cols - 8, "COINS");
	mvwprintw(stdscr, 2, 3, "%d", g->score);
	mvwprintw(stdscr, 2, g->cols / 2 - 2, "%d", g->time);
	mvwprintw(stdscr, 2, g->cols - 8, "%d", g->coins);
	wattroff(stdscr, COLOR_PAIR(WHITE_BLUE));
	pnoutrefresh(g->m->pad, 0, g->p->x - g->cols / 5, 0, 0, g->rows - 1, g->cols - 1);
	wnoutrefresh(stdscr);
	doupdate();
}
//Clears a component off the 2-D array
void clrgstate(game *g, int y, int x, int rows, int cols) {
	int i, j;
	for(i = y; i < y + rows; i++) {
		for(j = x; j < x + cols; j++)
			g->state[i][j] = 'n';
	}
} 
//Updates a component of the 2-D array
void updategstate(game *g, int y, int x, int rows, int cols, char ch) {
	int i, j;
	for(i = y; i < y + rows; i++) {
		for(j = x; j < x + cols; j++) 
			g->state[i][j] = ch;
	}
}
