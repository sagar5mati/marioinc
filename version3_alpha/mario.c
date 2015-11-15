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
//Initializes the mario structure
void initmario(game *g) {
	g->p = (mario *)malloc(sizeof(mario));
	mario *m = g->p;
	m->y = 5 * g->rows / 6 - 2;
	m->x = g->cols / 5;
	m->state = 'a';
	m->life = 3;
	m->b.state = 0;
	m->b.y = 0;
	m->b.x = 0; 
}
//Print mario on pad 
void printmario(game *g) {
	mario *t = g->p;
	WINDOW *pad = g->m->pad;
	wattron(pad, COLOR_PAIR(g->m->color));
	switch(t->state) {
		case 'a':
		case 'd':
		case 'f': mvwprintw(pad, t->y, t->x + 1, "Q");
			  mvwprintw(pad, t->y + 1, t->x, "/ \\");
			  break;
		case 'b': mvwprintw(pad, t->y, t->x, "<Q>");
			  break;
		case 'c': 
		case 'e': mvwprintw(pad, t->y, t->x + 1, "Q");
			  mvwprintw(pad, t->y + 1, t->x, "<#>");
			  mvwprintw(pad, t->y + 2, t->x, "/ \\");
			  break;
		default:  break;
	}
	wattroff(pad, COLOR_PAIR(g->m->color));
	if(t->b.state) 
		printbullet(g);
}
//Move mario, change its position
int movemario_small(game *g, char direc) {
	mario *t = g->p;
	int i, j, k;
	switch(direc) {
		case 'd':
			if(t->x == g->m->cols - 1)
				break;
			if(isobstacle(g, 'd', 2, 3, t->y, t->x))
				break;
			clrgstate(g, t->y, t->x, 2, 3);
			t->x++;
			updategstate(g, t->y, t->x, 2, 3, 'm');
			break;
		case 'a':
			if(t->x == 0)
				break;
			if(isobstacle(g, 'a', 2, 3, t->y, t->x))
				break;
			clrgstate(g, t->y, t->x, 2, 3);
			t->x--;
			updategstate(g, t->y, t->x, 2, 3, 'm');
			break;
		case 's':
			clrgstate(g, t->y, t->x, 2, 3);
			t->state = 'b';
			t->y++;
			updategstate(g, t->y, t->x, 1, 3, 'm');
			updatescreen(g);
			napms(50);
			clrgstate(g, t->y, t->x, 1, 3);
			t->y--;
			t->state = 'a';
			updategstate(g, t->y, t->x, 2, 3, 'm');
			updatescreen(g);
			flushinp();
			break;
		case 'z':
			if(t->state != 'b') {
				clrgstate(g, t->y, t->x, 2, 3);
				t->state = 'b';
				t->y++;
				updategstate(g, t->y, t->x, 1, 3, 'm');
				updatescreen(g);
			}
			if(!isobstacle(g, 'a', 1, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 1, 3);
				t->x--;
				updategstate(g, t->y, t->x, 1, 3, 'm');
				updatescreen(g);
			}
			else
				napms(50);
			if(!isobstacle(g, 'w', 1, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 1, 3);
				t->y--;
				t->state = 'a';
				updategstate(g, t->y, t->x, 2, 3, 'm');				
				updatescreen(g);
			}
			flushinp();
			break;
		case 'x':
			if(t->state != 'b') {
				clrgstate(g, t->y, t->x, 2, 3);
				t->state = 'b';
				t->y++;
				updategstate(g, t->y, t->x, 1, 3, 'm');
				updatescreen(g);
			}
			if(!isobstacle(g, 'd', 1, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 1, 3);
				t->x++;
				updategstate(g, t->y, t->x, 1, 3, 'm');
				updatescreen(g);
			}
			else
				napms(50);
			if(!isobstacle(g, 'w', 1, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 1, 3);
				t->y--;
				t->state = 'a';
				updategstate(g, t->y, t->x, 2, 3, 'm');
				updatescreen(g);
			}
			flushinp();
			break;
		case 'w':
			i = 2;
			while(i--) {
				j = isobstacle(g, 'w', 2, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y--;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
				}
				else if(j + 'n' == 'b' || j + 'n' == 'a') {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
				else
					break;
				napms(50);
			}
			flushinp();
			break;	
		case 'e':
			i = 2, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 2, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y--;
					if(isobstacle(g, 'd', 2, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x++;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 1;
			while(i--) {
				if(!isobstacle(g, 's', 2, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y++;
					if(isobstacle(g, 'd', 2, 3, t->y, t->x))
						break;
					t->x++;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}			
			flushinp();
			break;
		case 'q':
			i = 2, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 2, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y--;
					if(isobstacle(g, 'a', 2, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x--;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 1;
			while(i--) {
				if(!isobstacle(g, 's', 2, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y++;
					if(isobstacle(g, 'a', 2, 3, t->y, t->x))
						break;
					t->x--;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}	
			flushinp(); 
			break;
		case 't':
			i = 4, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 2, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y--;
					if(isobstacle(g, 'd', 2, 3, t->y, t->x)) {
						k = 1;
						break;
					}
					t->x++;
					if(isobstacle(g, 'd', 2, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x++;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 3;
			while(i--) {
				if(!isobstacle(g, 's', 2, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y++;
					if(isobstacle(g, 'd', 2, 3, t->y, t->x))
						break;
					t->x++;
					if(isobstacle(g, 'd', 2, 3, t->y, t->x))
						break;
					t->x++;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}			
			flushinp();
			break;		
		case 'r':
			i = 4, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 2, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y--;
					if(isobstacle(g, 'a', 2, 3, t->y, t->x)) {
						k = 1;
						break;
					}
					t->x--;
					if(isobstacle(g, 'a', 2, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x--;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 3;
			while(i--) {
				if(!isobstacle(g, 's', 2, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 2, 3);
					t->y++;
					if(isobstacle(g, 'a', 2, 3, t->y, t->x))
						break;
					t->x--;
					if(isobstacle(g, 'a', 2, 3, t->y, t->x))
						break;
					t->x--;
					updategstate(g, t->y, t->x, 2, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}			
			flushinp(); 
			break;						
		default :  
			break;
	} 
	return pitfall(g);
}
//Move mario change its position
int movemario_big(game *g, char direc) {
	mario *t = g->p;
	int i, j, k;
	switch(direc) {
		case 'd':
			if(t->x == g->m->cols - 1)
				break;
			if(isobstacle(g, 'd', 3, 3, t->y, t->x))
				break;
			clrgstate(g, t->y, t->x, 3, 3);
			t->x++;
			updategstate(g, t->y, t->x, 3, 3, 'm');
			flushinp();
			break;
		case 'a':
			if(t->x == 0)
				break;
			if(isobstacle(g, 'a', 3, 3, t->y, t->x))
				break;
			clrgstate(g, t->y, t->x, 3, 3);
			t->x--;
			updategstate(g, t->y, t->x, 3, 3, 'm');
			flushinp();
			break;
		case 's':
			clrgstate(g, t->y, t->x, 3, 3);
			if(t->state == 'c')
				t->state = 'd';
			else
				t->state = 'f';
			t->y++;
			updategstate(g, t->y, t->x, 2, 3, 'm');
			updatescreen(g);
			napms(50);
			clrgstate(g, t->y, t->x, 2, 3);
			t->y--;
			if(t->state == 'd') 
				t->state = 'c';
			else
				t->state = 'e';
			updategstate(g, t->y, t->x, 3, 3, 'm');
			updatescreen(g);
			flushinp();
			break;
		case 'z':
			if(t->state != 'd' && t->state != 'f') {
				clrgstate(g, t->y, t->x, 3, 3);
				if(t->state == 'c')
					t->state = 'd';
				else
					t->state = 'e';
				t->y++;
				updategstate(g, t->y, t->x, 2, 3, 'm');
				updatescreen(g);
			}
			if(!isobstacle(g, 'a', 2, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 2, 3);
				t->x--;
				updategstate(g, t->y, t->x, 3, 3, 'm');
				updatescreen(g);
			}
			else
				napms(50);
			if(!isobstacle(g, 'w', 2, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 2, 3);
				t->y--;
				if(t->state == 'd') 
					t->state = 'c';
				else
					t->state = 'e';
				updategstate(g, t->y, t->x, 3, 3, 'm');				
				updatescreen(g);
			}
			flushinp();
			break;
		case 'x':
			if(t->state != 'd' && t->state != 'f') {
				clrgstate(g, t->y, t->x, 3, 3);
				if(t->state == 'c')
					t->state = 'd';
				else
					t->state = 'f';
				t->y++;
				updategstate(g, t->y, t->x, 2, 3, 'm');
				updatescreen(g);
			}
			if(!isobstacle(g, 'd', 2, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 2, 3);
				t->x++;
				updategstate(g, t->y, t->x, 3, 3, 'm');
				updatescreen(g);
			}
			else
				napms(50);
			if(!isobstacle(g, 'w', 2, 3, t->y, t->x)) {
				clrgstate(g, t->y, t->x, 2, 3);
				t->y--;
				if(t->state == 'd') 
					t->state = 'c';
				else
					t->state = 'e';
				updategstate(g, t->y, t->x, 3, 3, 'm');
				updatescreen(g);
			}
			flushinp();
			break;
		case 'w':
			i = 3;
			while(i--) {
				j = isobstacle(g, 'w', 3, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y--;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a')
					break;
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
				napms(50);
			}
			flushinp();
			break;	
		case 'e':
			i = 3, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 3, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y--;
					if(isobstacle(g, 'd', 3, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x++;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 2;
			while(i--) {
				if(!isobstacle(g, 's', 3, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y++;
					if(isobstacle(g, 'd', 3, 3, t->y, t->x))
						break;
					t->x++;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}			
			flushinp();
			break;
		case 'q':
			i = 3, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 3, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y--;
					if(isobstacle(g, 'a', 3, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x--;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 2;
			while(i--) {
				if(!isobstacle(g, 's', 3, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y++;
					if(isobstacle(g, 'a', 3, 3, t->y, t->x))
						break;
					t->x--;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}	
			flushinp(); 
			break;
		case 't':
			i = 6, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 3, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y--;
					if(isobstacle(g, 'd', 3, 3, t->y, t->x)) {
						k = 1;
						break;
					}
					t->x++;
					if(isobstacle(g, 'd', 3, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x++;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 5;
			while(i--) {
				if(!isobstacle(g, 's', 3, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y++;
					if(isobstacle(g, 'd', 3, 3, t->y, t->x))
						break;
					t->x++;
					if(isobstacle(g, 'd', 3, 3, t->y, t->x))
						break;
					t->x++;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}			
			flushinp();
			break;		
		case 'r':
			i = 6, k = 0;
			while(i--) {
				j = isobstacle(g, 'w', 3, 3, t->y, t->x);
				if(!j) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y--;
					if(isobstacle(g, 'a', 3, 3, t->y, t->x)) {
						k = 1;
						break;
					}
					t->x--;
					if(isobstacle(g, 'a', 3, 3, t->y, t->x)) {
						k = 1;					
						break;
					}
					t->x--;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
					napms(50);
				}
				else if(j + 'n' != 'b' && j + 'n' != 'a') {
					k = 1;
					break;
				}
				else {
					k = getbrickindex(g);
					if(j + 'n' == 'b')					
						destroybrick(g, k);
					if(j + 'n' == 'a')
						destroymoney(g, k);
					updatescreen(g);
					break;
				}
			}
			if(k)
				break;
			i = 5;
			while(i--) {
				if(!isobstacle(g, 's', 3, 3, t->y, t->x)) {
					clrgstate(g, t->y, t->x, 3, 3);
					t->y++;
					if(isobstacle(g, 'a', 3, 3, t->y, t->x))
						break;
					t->x--;
					if(isobstacle(g, 'a', 3, 3, t->y, t->x))
						break;
					t->x--;
					updategstate(g, t->y, t->x, 3, 3, 'm');
					updatescreen(g);
				}
				else
					break;
			}			
			flushinp(); 
			break;						
		default :  
			break;
	} 
	return pitfall(g);	
}
//Print bullet on pad
void printbullet(game *g) {
	bullet *t = &g->p->b;
	int temp = 1;
	switch(g->state[t->y][t->x + 1]) {
		case 'b':
		case 'p':
		case 'w':
			t->state = 0;
			temp = 0;
			break;
		default:
			if(g->state[t->y][t->x + 1] >= '0' && g->state[t->y][t->x + 1] <= '9') {
				t->state = 0;
				temp = 0;
			}
			break;
	}
	if(temp) {		
		wattron(g->m->pad, COLOR_PAIR(RED_BLUE) | A_BOLD);
		mvwaddch(g->m->pad, t->y, t->x, '-');
		wattroff(g->m->pad, COLOR_PAIR(RED_BLUE) | A_BOLD);
		t->x++;
		napms(25);
	}
}
//Make mario fall if not standing on some support
int pitfall(game *g) {
	int i = 0, r = 0;
	mario *t = g->p;
	while(1) {
		switch(t->state) {
			case 'a':
			case 'd':
			case 'f':
				if(t->y + 2 == g->rows)
					r = 1;
				i = isobstacle(g, 's', 2, 3, t->y, t->x);
				break;
			case 'b':
				if(t->y + 1 == g->rows)
					r = 1;
				i = isobstacle(g, 's', 1, 3, t->y, t->x);
				break;
			case 'c':
			case 'e':
				if(t->y + 3 == g->rows)
					r = 1;
				i = isobstacle(g, 's', 3, 3, t->y, t->x);
				break;
			default:
				break;
		}
		if(r)
			break;
		if(i)
			break;
		if(t->state == 'a' || t->state == 'd' || t->state == 'f') 		
			clrgstate(g, t->y, t->x, 2, 3);
		else if(t->state == 'c' || t->state == 'e')
			clrgstate(g, t->y, t->x, 3, 3);
		else
			clrgstate(g, t->y, t->x, 1, 3);
		t->y++;
		if(t->state == 'a' || t->state == 'd' || t->state == 'f') 
			updategstate(g, t->y, t->x, 2, 3, 'm');
	 	else if(t->state == 'c' || t->state == 'e')
			updategstate(g, t->y, t->x, 3, 3, 'm');
		else 
			updategstate(g, t->y, t->x, 1, 3, 'm');
		updatescreen(g);
		i = 0;
	}
	return r;
}
//Get the index of the brick to be destroyed
int getbrickindex(game *g) {
	mario *t = g->p;
	int i = 1, j = 0, num = 0, k = 4, l = 0;
	char c, d, e;
	c = g->state[t->y - 1][t->x]; 
	d = g->state[t->y - 1][t->x + 1]; 
	e = g->state[t->y - 1][t->x + 2];
	while(c != 'b' && c != 'a' && d != 'b' && d != 'a' && e != 'b' && e != 'a') {
		i++;
		c = g->state[t->y - i][t->x];  
		d = g->state[t->y - i][t->x + 1]; 
		e = g->state[t->y - i][t->x + 2];
	}
	if(c == 'b') {
		while(c == 'b') {
			j++;
			c = g->state[t->y - i][t->x - j];
			l = 0;
		}
	}
	else if(c == 'a') {
		while(c == 'a') {
			j++;
			c = g->state[t->y - i][t->x - j];
			l = 0;
		}
	}
	if(!(g->state[t->y - i][t->x + 1 - j] == 'b' || g->state[t->y - i][t->x + 1 - j] == 'a')) {
		if(d == 'b') {		
			while(d == 'b') {
				j++;
				d = g->state[t->y - i][t->x + 1 - j];
				l = 1;
			}
		}
		else if(d == 'a') {
			while(d == 'a') {
				j++;
				d = g->state[t->y - i][t->x + 1 - j];
				l = 1;
			}
		}
		if(!(g->state[t->y - i][t->x + 1 - j] == 'b' || g->state[t->y - i][t->x + 1 - j] == 'a')) {
			if(e == 'b') {			
				while(e == 'b') {
					j++;
					e = g->state[t->y - i][t->x + 2 - j];
					l = 2;
				}
			}
			else if(e == 'a') {
				while(e == 'a') {
					j++;
					e = g->state[t->y - i][t->x + 2 - j];
					l = 2;
				}
			}
		}
	}
	while(k--) {
		num = num * 10 + g->state[t->y - i - 1][t->x + l - j + 1] - 48;
		j--;
	}	
	clrgstate(g, t->y - i - 1, t->x - 3 - j, 2, 4);
	return num;		 	
} 
//Read from a file
void readmario(game *g, FILE *fp) {
	mario *t = g->p;
	fscanf(fp, "%d %d %d %c %d %d %d ", &t->y, &t->x, &t->life, &t->state, &t->b.y, &t->b.x, &t->b.state);
}
//Write to a file
void writemario(game *g, FILE *fp) {
	mario *t = g->p;
	fprintf(fp, "%d %d %d %c %d %d %d ", t->y, t->x, t->life, t->state, t->b.y, t->b.x, t->b.state);
}
