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
//Initializes color and color pairs
void initcolor(void) {
	if(has_colors()) 
		start_color();
	else
		return;
	init_pair(1, COLOR_WHITE, COLOR_RED);
	init_pair(2, COLOR_WHITE, COLOR_BLUE);
	init_pair(3, COLOR_WHITE, COLOR_GREEN);
	init_pair(4, COLOR_WHITE, COLOR_WHITE);
	init_pair(5, COLOR_WHITE, COLOR_BLACK);
	init_pair(6, COLOR_WHITE, COLOR_YELLOW);
	init_pair(7, COLOR_WHITE, COLOR_MAGENTA);
	init_pair(8, COLOR_WHITE, COLOR_CYAN);
	init_pair(9, COLOR_BLACK, COLOR_RED);
	init_pair(10, COLOR_BLACK, COLOR_BLUE);
	init_pair(11, COLOR_BLACK, COLOR_GREEN);
	init_pair(12, COLOR_BLACK, COLOR_WHITE);
	init_pair(13, COLOR_BLACK, COLOR_BLACK);
	init_pair(14, COLOR_BLACK, COLOR_YELLOW);
	init_pair(15, COLOR_BLACK, COLOR_MAGENTA);
	init_pair(16, COLOR_BLACK, COLOR_CYAN);
	init_pair(17, COLOR_RED, COLOR_RED);
	init_pair(18, COLOR_RED, COLOR_BLUE);
	init_pair(19, COLOR_RED, COLOR_GREEN);
	init_pair(20, COLOR_RED, COLOR_WHITE);
	init_pair(21, COLOR_RED, COLOR_BLACK);
	init_pair(22, COLOR_RED, COLOR_YELLOW);
	init_pair(23, COLOR_RED, COLOR_MAGENTA);
	init_pair(24, COLOR_RED, COLOR_CYAN);
	init_pair(25, COLOR_BLUE, COLOR_RED);
	init_pair(26, COLOR_BLUE, COLOR_BLUE);
	init_pair(27, COLOR_BLUE, COLOR_GREEN);
	init_pair(28, COLOR_BLUE, COLOR_WHITE);
	init_pair(29, COLOR_BLUE, COLOR_BLACK);
	init_pair(30, COLOR_BLUE, COLOR_YELLOW);
	init_pair(31, COLOR_BLUE, COLOR_MAGENTA);
	init_pair(32, COLOR_BLUE, COLOR_CYAN);
	init_pair(33, COLOR_GREEN, COLOR_RED);
	init_pair(34, COLOR_GREEN, COLOR_BLUE);
	init_pair(35, COLOR_GREEN, COLOR_GREEN);
	init_pair(36, COLOR_GREEN, COLOR_WHITE);
	init_pair(37, COLOR_GREEN, COLOR_BLACK);
	init_pair(38, COLOR_GREEN, COLOR_YELLOW);
	init_pair(39, COLOR_GREEN, COLOR_MAGENTA);
	init_pair(40, COLOR_GREEN, COLOR_CYAN);
	init_pair(41, COLOR_YELLOW, COLOR_RED);
	init_pair(42, COLOR_YELLOW, COLOR_BLUE);
	init_pair(43, COLOR_YELLOW, COLOR_GREEN);
	init_pair(44, COLOR_YELLOW, COLOR_WHITE);
	init_pair(45, COLOR_YELLOW, COLOR_BLACK);
	init_pair(46, COLOR_YELLOW, COLOR_YELLOW);
	init_pair(47, COLOR_YELLOW, COLOR_MAGENTA);
	init_pair(48, COLOR_YELLOW, COLOR_CYAN);
	init_pair(49, COLOR_MAGENTA, COLOR_RED);
	init_pair(50, COLOR_MAGENTA, COLOR_BLUE);
	init_pair(51, COLOR_MAGENTA, COLOR_GREEN);
	init_pair(52, COLOR_MAGENTA, COLOR_WHITE);
	init_pair(53, COLOR_MAGENTA, COLOR_BLACK);
	init_pair(54, COLOR_MAGENTA, COLOR_YELLOW);
	init_pair(55, COLOR_MAGENTA, COLOR_MAGENTA);
	init_pair(56, COLOR_MAGENTA, COLOR_CYAN);
	init_pair(57, COLOR_CYAN, COLOR_RED);
	init_pair(58, COLOR_CYAN, COLOR_BLUE);
	init_pair(59, COLOR_CYAN, COLOR_GREEN);
	init_pair(60, COLOR_CYAN, COLOR_WHITE);
	init_pair(61, COLOR_CYAN, COLOR_BLACK);
	init_pair(62, COLOR_CYAN, COLOR_YELLOW);
	init_pair(63, COLOR_CYAN, COLOR_MAGENTA);
	init_pair(64, COLOR_CYAN, COLOR_CYAN);	
}
