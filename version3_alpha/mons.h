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
typedef struct turt {
	int y, x, state, color, direc;
}turt;
typedef struct mons {
	int nt;
	turt *t;
}mons;
void initmons(game *g);
void readmons(game *g, FILE *fp);
void writemons(game *g, FILE *fp);
void printmons(game *g);
void moveturt(game *g);
void readturt(game *g, FILE *fp);
void writeturt(game *g, FILE *fp);
void printturt(game *g, turt *t);
void *movethings(void *g);
void pitmons(game *g, turt *t);
