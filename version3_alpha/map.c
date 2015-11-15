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
//Initializes the map structure
void initmap(game *g) {
	int fp;
	g->m = (map *)malloc(sizeof(map));	
	map *t = g->m;
	fp = open("level0-0", O_RDONLY);
	read(fp, t, sizeof(map));
	t->b = (bricks *)malloc(t->nb * sizeof(bricks));
	t->m = (money *)malloc(t->nm * sizeof(money));
	t->p = (pipes *)malloc(t->np * sizeof(pipes));
	t->w = (wall *)malloc(t->nw * sizeof(wall));
	t->h = (holes *)malloc(t->nh * sizeof(holes));
	t->s = (stairs *)malloc(t->ns * sizeof(stairs));
	read(fp, t->b, t->nb * sizeof(bricks));
	read(fp, t->m, t->nm * sizeof(money));
	read(fp, t->p, t->np * sizeof(pipes));
	read(fp, t->w, t->nw * sizeof(wall));
	read(fp, t->h, t->nh * sizeof(holes));
	read(fp, t->s, t->ns * sizeof(stairs));
	close(fp);
	t->pad = newpad(t->rows, t->cols);
}
//Draws the map on the pad
void drawmap(game *g) {
	map *t = g->m;
	int nb = t->nb, nw = t->nw, np = t->np, ns = t->ns, nm = t->nm, nh = t-> nh;	
	wbkgd(t->pad, COLOR_PAIR(t->color));
	while(nb--)
		drawbricks(g, &t->b[nb], nb);
	while(nm--)
		drawmoney(g, &t->m[nm], nm);
	while(np--)
		drawpipes(g, &t->p[np]);
	while(nw--)
		drawwall(g, &t->w[nw]);
	while(nh--)
		drawholes(g, &t->h[nh]);
	while(ns--)
		drawstairs(g, &t->s[ns]);
}		
//Draw bricks on the pad 
void drawbricks(game *g, bricks *b, int ind) {
	int i, j;
	for(i = b->y; i < b->y + 2; i++) {
		for(j = b->x; j < b->x + 4; j++) {
			wattron(g->m->pad, COLOR_PAIR(b->color) | A_BOLD);
			mvwaddch(g->m->pad, i, j, '+');
			wattroff(g->m->pad, COLOR_PAIR(b->color) | A_BOLD);			
			g->state[i][j] = 'b';
		}
	}
	for(i = 3; i >= 0; i--) {
		g->state[b->y][b->x + i] = ind % 10 + 48;
		ind /= 10;
	}
}
//Draw money on the pad
void drawmoney(game *g, money *m, int ind){
	int i, j;
	if(m->state != -1) {
		for(i = m->y; i < m->y + 2; i++) {
			for(j = m->x; j < m->x + 4; j++) {
				if(m->state) {
					wattron(g->m->pad, COLOR_PAIR(RED_YELLOW) | A_BOLD);
					mvwaddch(g->m->pad, i, j, '?');
					wattroff(g->m->pad, COLOR_PAIR(RED_YELLOW) | A_BOLD);
				}	
				g->state[i][j] = 'a';
			}
		}
		for(i = 3; i >= 0; i--) {
			g->state[m->y][m->x + i] = ind % 10 + 48;
			ind /= 10;
		}
	}
	else {
		for(i = m->y; i < m->y + 2; i++) {
			for(j = m->x; j < m->x + 4; j++) {
				wattron(g->m->pad, COLOR_PAIR(RED_YELLOW) | A_BOLD);
				mvwaddch(g->m->pad, i, j, ' ');
				wattroff(g->m->pad, COLOR_PAIR(RED_YELLOW) | A_BOLD);
				g->state[i][j] = 'w';
			}
		}
	}
}	
//Draw pipes on the pad
void drawpipes(game *g, pipes *p) {
	int i, j;
	for(i = p->y; i < p->y + p->height * 2; i++) {
		for(j = p->x; j < p->x + 10; j++) {
			wattron(g->m->pad, COLOR_PAIR(WHITE_GREEN));
			if(i <= p->y + 1)
				mvwaddstr(g->m->pad, i, j, " ");
			else if(j < p->x + 8)
				mvwaddstr(g->m->pad, i, j + 1, " ");
			wattroff(g->m->pad, COLOR_PAIR(WHITE_GREEN));
			g->state[i][j] = 'p';
		}
	}
}	
//Draw wall on the pad
void drawwall(game *g, wall *w) {
	int i, j;
	for(i = w->y; i < w->y + w->rows; i++) {
		for(j = w->x; j < w->x + w->cols; j++) {
			wattron(g->m->pad, COLOR_PAIR(WHITE_RED));
			mvwaddch(g->m->pad, i, j, ' ');
			wattroff(g->m->pad, COLOR_PAIR(WHITE_RED));
			g->state[i][j] = 'w';
		}
	} 
}
//Draw holes on the pad
void drawholes(game *g, holes *h){
	int i, j;
	for(i = h->y; i < h->y + h->rows; i++) {
		for(j = h->x; j < h->x + h->cols; j++) {
			wattron(g->m->pad, COLOR_PAIR(WHITE_BLUE));
			mvwaddch(g->m->pad, i, j, ' ');
			wattroff(g->m->pad, COLOR_PAIR(WHITE_BLUE));
			g->state[i][j] = 'n';
		}
	}
}
//Draw stairs on the pad
void drawstairs(game *g, stairs *s) {
	int i, j, n = 0;
	for(i = s->x - 2 + s->cols * 3; i >= s->x; i -= 3) {
		 for(j = s->y + n;  j < s->y + s->rows; j++) {
			wattron(g->m->pad, COLOR_PAIR(WHITE_RED) | A_DIM);
			mvwaddstr(g->m->pad, j, i, "   ");
			mvwaddstr(g->m->pad, j, i, "   ");
			wattroff(g->m->pad, COLOR_PAIR(WHITE_RED) | A_DIM);
			g->state[j][i] = 's';
			g->state[j][i + 1] = 's';
			g->state[j][i + 2] = 's';
		}
		n++;
	}
}
//Check for obstacles around a component			 
int isobstacle(game *g, char direc, int rows, int cols, int y, int x) {
	int i;	
	int r = 'n';
	switch(direc) {
		case 'd':
			for(i = 0; i < rows; i++) {
				switch(g->state[y + i][x + cols]) {
					case 'b':
						r = 'b';
						break;
					case 'p':
						r = 'p';
						break;
					case 'w':
						r = 'w';
						break;
					case 'm':
						r = 'm';
						break;
					case 's':						
						r = 's';
						break;
					case 'a':
						r = 'a';
						break;
					case 'x':
						r = 'x';
						break;
					default :
						if(g->state[y + i][x + cols] >= '0' 
							&& g->state[y + i][x + cols] <= '9')
						r = 'b';
						break;
				}
			}
			break;
		case 'a':
			for(i = 0; i < rows; i++) {
				switch(g->state[y + i][x - 1]) {
					case 'b':
						r = 'b';
						break;
					case 'p':
						r = 'p';
						break;
					case 'w':
						r = 'w';
						break;
					case 's':
						r = 's';
						break;
					case 'm':
						r = 'm';
						break;
					case 'a':
						r = 'a';
						break;
					case 'x':
						r = 'x';
						break;
					default :
						if(g->state[y + i][x - 1] >= '0' 
							&& g->state[y + i][x - 1] <= '9')
						r = 'b';
						break;
				}
			}
			break;
		case 's':
			if(y + rows == g->rows) {
				r = 'w';
				break;
			}
			for(i = 0; i < cols; i++) {
				switch(g->state[y + rows][x + i]) {
					case 'b':
						r = 'b';
						break;
					case 'p':
						r = 'p';
						break;
					case 'e':
						r = 'e';
						break;
					case 'w':
						r = 'w';
						break;
					case 's':
						r = 's';
						break;
					case 'm':
						r = 'm';
						break;
					case 'a':
						r = 'a';
						break;
					case 'x':
						r = 'x';
						break;
					default :
						if(g->state[y + rows][x + i] >= '0' 
							&& g->state[y + rows][x + i] <= '9')
						r = 'b';
						break;
				}
			}
			break;
		case 'w':
			if(y == 0) {
				r = 'w';
				break;
			}
			for(i = 0; i < cols; i++) {
				switch(g->state[y - 1][x + i]) {
					case 'b':
						r = 'b';
						break;
					case 'm':
						r = 'm';
						break;
					case 'a':
						r = 'a';
						break;
					case 'w':
						r = 1;
						break;
					case 'x':
						r = 'x';
						break;
					default:
						break;
				}
			}
			break;
		default:
			break;
	}
	return r - 'n';
}
//Destroy a brick	
void destroybrick(game *g, int ind) {
	map *t = g->m;	
	int nb = t->nb, i;
	if(t->b[ind].state == 2) {
		switch(g->p->state) {
			case 'a':			
				clrgstate(g, g->p->y, g->p->x, 2, 3);
				g->p->state = 'c';
				g->p->y--;
				updategstate(g, g->p->y, g->p->x, 3, 3, 'm');
				break;
			case 'c':
				g->p->state = 'e';
				break;
			default:
				break;
		}
	}			 
	if(t->b[ind].num == 1) {
		clrgstate(g, t->b[ind].y, t->b[ind].x, 2, 4);
		for(i = ind + 1; i < nb; i++) {
			t->b[i - 1] = t->b[i];
		}
		t->nb--;
		g->coins++;
		g->score += 10;
	}
	else { 
		t->b[ind].num--;
		g->coins++;
		g->score += 10;
		drawbricks(g, &t->b[ind], ind);
	}
}
//Destroy a money brick
void destroymoney(game *g, int ind) {
	map *t = g->m;
	if(t->m[ind].state == 0) 
		g->p->life++;
	if(t->m[ind].num == 1) {
		clrgstate(g, t->m[ind].y, t->m[ind].x, 2, 4);		
		t->m[ind].state = -1;
		g->coins += 2;
		g->score += 50;
		drawmoney(g, &t->m[ind], ind);
	}
	else { 
		g->coins += 2;
		g->score += 50;
		t->m[ind].num--;
		drawmoney(g, &t->m[ind], ind);
	}
}	
//Read map from a file
void readmap(game *g, FILE *fp) {
	map *t = g->m;
	int i;
	fscanf(fp, "%d %d %d %d %d %d %d %d %d ",
		 &t->rows, &t->cols, &t->color, &t->nb, &t->np, &t->nw, &t->ns, &t->nm, &t->nh);
	for(i = 0; i < t->nb; i++)
		fscanf(fp, "%d %d %d %d %d ", &t->b[i].y, &t->b[i].x, &t->b[i].color, &t->b[i].num, &t->b[i].state);
	for(i = 0; i < t->np; i++) 
		fscanf(fp, "%d %d %d %d ", &t->p[i].y, &t->p[i].x, &t->p[i].height, &t->p[i].state);
	for(i = 0; i < t->nw; i++) 
		fscanf(fp, "%d %d %d %d ", &t->w[i].rows, &t->w[i].cols, &t->w[i].y, &t->w[i].x);
	for(i = 0; i < t->ns; i++) 
		fscanf(fp, "%d %d %d %d %d ", &t->s[i].rows, &t->s[i].cols, &t->s[i].y, &t->s[i].x, &t->s[i].color);
	for(i = 0; i < t->nm; i++) 
		fscanf(fp, "%d %d %d %d ", &t->m[i].y, &t->m[i].x, &t->m[i].state, &t->m[i].num);
	for(i = 0; i < t->nh; i++) 
		fscanf(fp, "%d %d %d %d ", &t->h[i].rows, &t->h[i].cols, &t->h[i].y, &t->h[i].x);	
}
//Write map to a file 
void writemap(game *g, FILE *fp) {
	map *t = g->m;
	int i;
	fprintf(fp, "%d %d %d %d %d %d %d %d %d ", 
			t->rows, t->cols,t->color, t->nb, t->np, t->nw, t->ns, t->nm, t->nh);
	for(i = 0; i < t->nb; i++) 
		fprintf(fp, "%d %d %d %d %d ", t->b[i].y, t->b[i].x, t->b[i].color, t->b[i].num, t->b[i].state);
	for(i = 0; i < t->np; i++) 
		fprintf(fp, "%d %d %d %d ", t->p[i].y, t->p[i].x, t->p[i].height, t->p[i].state);
	for(i = 0; i < t->nw; i++) 
		fprintf(fp, "%d %d %d %d ", t->w[i].rows, t->w[i].cols, t->w[i].y, t->w[i].x);
	for(i = 0; i < t->ns; i++) 
		fprintf(fp, "%d %d %d %d %d ", t->s[i].rows, t->s[i].cols, t->s[i].y, t->s[i].x, t->s[i].color);
	for(i = 0; i < t->nm; i++) 
		fprintf(fp, "%d %d %d %d ", t->m[i].y, t->m[i].x, t->m[i].state, t->m[i].num);
	for(i = 0; i < t->nh; i++) 
		fprintf(fp, "%d %d %d %d ", t->h[i].rows, t->h[i].cols, t->h[i].y, t->h[i].x);	
}
