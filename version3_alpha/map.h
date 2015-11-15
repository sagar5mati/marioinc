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
typedef struct bricks {
	int y, x, color, num, state;
}bricks;
typedef struct pipes {
	int y, x, height, state;
}pipes;
typedef struct stairs {
	int rows, cols, y, x, color;
}stairs;
typedef struct money {
	int y, x, state, num;
}money;
typedef struct holes {
	int rows, cols, y, x;
}holes;
typedef struct wall {
	int rows, cols, y, x, color;
}wall;
typedef struct map {
	char name[21];
	WINDOW *pad;
	int rows, cols, color;
	int nb, np, nw, ns, nm, nh;
	bricks *b;
	pipes *p;
	wall *w;
	stairs *s;
	money *m;
	holes *h;
}map;
void initmap(game *g);
void drawmap(game *g);
void drawbricks(game *g, bricks *b, int ind);
void drawpipes(game *g, pipes *p);
void drawwall(game *g, wall *w);
int isobstacle(game *g, char direc, int rows, int cols, int y, int x);
void destroybrick(game *g, int ind);
void destroymoney(game *g, int ind);
void readmap(game *g, FILE *fp);
void writemap(game *g, FILE *fp);
void drawstairs(game *g, stairs *s);
void drawmoney(game *g, money *m, int ind);
void drawholes(game *g, holes *h);
void drawwall(game *g, wall *w);
