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
//Program starts here
int main() {
	gameinfo g;
	initgameinfo(&g);
	initscr();
	refresh();
	createmap();
	createmons();
	curs_set(FALSE);
	noecho();
	nodelay(stdscr, TRUE);	
	keypad(stdscr, TRUE);
	initcolor();
	while(1) {	
		g = reporthere(g);
		if(g.menu == -1) 
			break;
	}	
	endwin();
	return 0;
}
