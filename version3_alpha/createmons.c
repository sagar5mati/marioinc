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
//Creates a rough sketch for saving the actual monster info
void createmons() {
	int fp;
	mons grr;
	turt kutra[9];
	grr.nt = 9;
	grr.t = NULL;
	kutra[0].y = 18;
	kutra[0].x = 108;
	kutra[0].state = 1;
	kutra[0].color = 10;
	kutra[0].direc = -1; 	
kutra[1].y = 18;
	kutra[1].x = 108;
	kutra[1].state = 1;
	kutra[1].color = 10;
	kutra[1].direc = -1; 	
kutra[2].y = 18;
	kutra[2].x = 108;
	kutra[2].state = 1;
	kutra[2].color = 10;
	kutra[2].direc = -1; 	
kutra[3].y = 18;
	kutra[3].x = 108;
	kutra[3].state = 1;
	kutra[3].color = 10;
	kutra[3].direc = -1; 	
kutra[4].y = 18;
	kutra[4].x = 108;
	kutra[4].state = 1;
	kutra[4].color = 10;
	kutra[4].direc = -1; 	
kutra[5].y = 18;
	kutra[5].x = 108;
	kutra[5].state = 1;
	kutra[5].color = 10;
	kutra[5].direc = -1; 	
kutra[6].y = 18;
	kutra[6].x = 108;
	kutra[6].state = 1;
	kutra[6].color = 10;
	kutra[6].direc = -1; 	
kutra[7].y = 18;
	kutra[7].x = 108;
	kutra[7].state = 1;
	kutra[7].color = 10;
	kutra[7].direc = -1; 	
kutra[8].y = 18;
	kutra[8].x = 108;
	kutra[8].state = 1;
	kutra[8].color = 10;
	kutra[8].direc = -1; 	
	fp = open("mons0-0", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(fp, &grr, sizeof(mons));
	write(fp, &kutra, sizeof(turt) * grr.nt);
	close(fp);
}	
