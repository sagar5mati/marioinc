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
//Initializes the structure mons
void initmons(game *g) {
	int fp;
	g->mo = (mons *)malloc(sizeof(mons));
	mons *t = g->mo;
	fp = open("mons0-0", O_RDONLY);
	read(fp, t, sizeof(mons));
	t->t = (turt *)malloc(sizeof(turt) * t->nt);
	read(fp, t->t, sizeof(turt) * t->nt);
	close(fp);
}
//Read from a file
void readmons(game *g, FILE *fp) {	
	mons *t = g->mo;
	fscanf(fp, "%d ", &t->nt);
	readturt(g, fp);
}
//Write to a file
void writemons(game *g, FILE *fp) {	
	mons *t = 	g->mo;
	fprintf(fp, "%d ", t->nt);
	writeturt(g, fp);
}	
//Print on the pad
void printmons(game *g) {
	mons *t = g->mo;
	int i;
	for(i = 0; i < t->nt; i++) 
		printturt(g, &t->t[i]);
}
//Read from a file
void readturt(game *g, FILE *fp) {
	int i;
	turt *t = g->mo->t;
	for(i = 0; i < g->mo->nt; i++)
		fscanf(fp, "%d %d %d %d %d ", &t[i].y, &t[i].x, &t[i].state, &t[i].color, &t[i].direc);
}
//Write to a file 
void writeturt(game *g, FILE *fp) {
	int i;
	turt *t = g->mo->t;
	for(i = 0; i < g->mo->nt; i++)
		fprintf(fp, "%d %d %d %d %d ", t[i].y, t[i].x, t[i].state, t[i].color, t[i].direc);
}
//Print on the pad
void printturt(game *g, turt *t) {
	int i, j;
	if(t->state) {
		wattron(g->m->pad, COLOR_PAIR(WHITE_BLUE));
		mvwaddstr(g->m->pad, t->y, t->x, "<#>");
		mvwaddstr(g->m->pad, t->y + 1, t->x, "' '");
		wattroff(g->m->pad, COLOR_PAIR(WHITE_BLUE));
		for(i = t->y; i < t->y + 2; i++) {
			for(j = t->x; j < t->x + 2; j++)
				g->state[i][j] = 'x';
		}
	}
}
//Move the turtle		
void moveturt(game *g) {
	int i, j, k;	
	turt *t = g->mo->t;
	for(i = 0; i < g->mo->nt; i++) {
		if(t[i].state && t[i].x >= g->p->x - g->cols / 5 - 2 && t[i].x <= g->p->x - 2 + 4 * g->cols / 5) {
			if(isobstacle(g, 'w', 2, 3, t[i].y, t[i].x) == -1) {
				t[i].state = 0;
				g->score += 100;
			} 
			if(t[i].direc == 1) {
				j = isobstacle(g, 'd', 2, 3, t[i].y, t[i].x); 
				k = isobstacle(g, 'a', 2, 3, t[i].y, t[i].x); 
				if(!j)
					t[i].direc *= 1;
				else
					t[i].direc *= -1;
				if(j == -1 || k == -1)
					g->exit = 3;				
			}
			if(t[i].direc == -1) {
				j = isobstacle(g, 'a', 2, 3, t[i].y, t[i].x);
				k = isobstacle(g, 'd', 2, 3, t[i].y, t[i].x); 
				if(!j)
					t[i].direc *= 1;
				else
					t[i].direc *= -1;
				if(j == -1 || k == -1)
			 		g->exit = 3;
			}
			clrgstate(g, t[i].y, t[i].x, 2, 3);
			t[i].x += t[i].direc;
			pitmons(g, &t[i]);
		}
	}
}
//Code same as pitfall for mons
void pitmons(game *g, turt *t) {
	int i = 0, r = 0;
	while(1) {
		if(t->y + 2 == g->rows) {
			t->state = 0;
			break;
		}
		i = isobstacle(g, 's', 2, 3, t->y, t->x);
		if(r)
			return;
		if(i)
			break;
		clrgstate(g, t->y, t->x, 2, 3);
		t->y++;
		updategstate(g, t->y, t->x, 2, 3, 'x');
		i = 0;
	}
	return;
}
//Function for the new thread
void *movethings(void *g) {
	int i = 0;
	game *t = (game *)g;	
	while(1) {
		if(t->exit == 2)
			continue;
		if(t->exit == 1)
			return NULL;
		usleep(150000);
		i++;		
		pthread_mutex_lock(&lock);
		if(!t->time || t->exit == 3)
			pthread_exit(NULL);		
		moveturt(t);
		if(i == 7) {		
			t->time--;
			i = 0;
		}
		pthread_mutex_unlock(&lock);
	}
}
