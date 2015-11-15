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
typedef struct bullet {
	int y, x, state;
}bullet;
typedef struct mario {
	int y, x;
	int life;
	char state;
	bullet b;
}mario;
void initmario(game *g);
void printmario(game *g);
int movemario_small(game *g, char direc);
int movemario_big(game *g, char direc);
void printbullet(game *g);
int pitfall(game *g);
int getbrickindex(game *g);
void readmario(game *g, FILE *fp);
void writemario(game *g, FILE *fp);
