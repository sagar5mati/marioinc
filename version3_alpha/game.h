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
typedef struct map map;
typedef struct mario mario;
typedef struct node node;
typedef struct mons mons;
typedef struct list {
	node *head;
	int count;
}list;
typedef struct game {
	int rows, cols;
	int score, coins;
	int exit;
	int time;
	map *m;
	mario *p;
	mons *mo;
	char **state;
	list game;
}game;
typedef struct gameinfo {
	char *name;
	int menu;
}gameinfo;
void initgameinfo(gameinfo *g);
void initgame(game *g);
gameinfo startgame(game *g);
gameinfo pausegame(game *g);
void updatescreen(game *g);
void clrgstate(game *g, int y, int x, int rows, int cols);
void updategstate(game *g, int y, int x, int rows, int cols, char ch);
gameinfo reporthere(gameinfo i);
void loadgame(game *g, char *name);
void savegame(game *g);
void readgstate(game *g, FILE *fp);
void writegstate(game *g, FILE *fp);
