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
//Creates a rough sketch for saving the actual map
void createmap() {
	int fp, i;
	map hash;
	bricks todo[29];//, todo1, todo2;
	money paisa[15];
	pipes guso[6];
	stairs chado[16];
	holes giro[3];
	wall support[1];
	strcpy(hash.name, "level1-1");
	hash.pad = NULL;
	hash.rows = 24;
	hash.cols = 1000;
	hash.color = WHITE_BLUE;
	hash.nb = 29;
	hash.np = 6;
	hash.nw = 1;
	hash.nm = 15;
	hash.ns = 16;
	hash.nh = 3;
	hash.b = NULL;
	hash.p = NULL;
	hash.w = NULL;
	hash.h = NULL;
	hash.m = NULL;
	hash.s = NULL;
	todo[0].color = BLACK_RED;
	todo[0].num = 1;
	todo[0].state = 1;
	todo[0].y = 15;
	todo[0].x = 100;
	todo[1].color = BLACK_RED;
	todo[1].num = 1;
	todo[1].state = 1;
	todo[1].y = 15;
	todo[1].x = 108;
	todo[2].color = BLACK_RED;
	todo[2].num = 1;
	todo[2].state = 2;
	todo[2].y = 15;
	todo[2].x = 116;
	todo[3].color = BLACK_RED;
	todo[3].num = 1;
	todo[3].state = 1;
	todo[3].y = 14;
	todo[3].x = 329;
	todo[4].color = BLACK_RED;
	todo[4].num = 1;
	todo[4].state = 2;
	todo[4].y = 14;
	todo[4].x = 337;
	for(i = 0; i < 8; i++) { 
		todo[5 + i].color = BLACK_RED;
		todo[5 + i].num = 1;
		todo[5 + i].state = 1;
		todo[5 + i].y = 8;
		todo[5 + i].x = 341 + i * 4;
	}
	for(i = 0; i < 3; i++) { 
		todo[13 + i].color = BLACK_RED;
		todo[13 + i].num = 1;
		todo[13 + i].state = 1;
		todo[13 + i].y = 8;
		todo[13 + i].x = 385 + i * 4;
	}
	todo[16].color = BLACK_RED;
	todo[16].num = 7;
	todo[16].state = 1;
	todo[16].y = 15;
	todo[16].x = 397;
	todo[17].color = BLACK_RED;
	todo[17].num = 1;
	todo[17].state = 2;
	todo[17].y = 15;
	todo[17].x = 417;
	todo[18].color = BLACK_RED;
	todo[18].num = 1;
	todo[18].state = 1;
	todo[18].y = 15;
	todo[18].x = 481;
	for(i = 0; i < 3; i++) { 
		todo[19 + i].color = BLACK_RED;
		todo[19 + i].num = 1;
		todo[19 + i].state = 1;
		todo[19 + i].y = 8;
		todo[19 + i].x = 489 + i * 4;
	}
	todo[22].color = BLACK_RED;
	todo[22].num = 1;
	todo[22].state = 1;
	todo[22].y = 8;
	todo[22].x = 517;
	todo[23].color = BLACK_RED;
	todo[23].num = 1;
	todo[23].state = 1;
	todo[23].y = 8;
	todo[23].x = 529;
	todo[24].color = BLACK_RED;
	todo[24].num = 1;
	todo[24].state = 1;
	todo[24].y = 15;
	todo[24].x = 521;
	todo[25].color = BLACK_RED;
	todo[25].num = 1;
	todo[25].state = 1;
	todo[25].y = 15;
	todo[25].x = 525;
	todo[26].color = BLACK_RED;
	todo[26].num = 1;
	todo[26].state = 1;
	todo[26].y = 14;
	todo[26].x = 708;
	todo[27].color = BLACK_RED;
	todo[27].num = 1;
	todo[27].state = 1;
	todo[27].y = 14;
	todo[27].x = 712;
	todo[28].color = BLACK_RED;
	todo[28].num = 1;
	todo[28].state = 1;
	todo[28].y = 14;
	todo[28].x = 720;
	paisa[0].y = 15;
	paisa[0].x = 90;
	paisa[0].state = 1;
	paisa[0].num = 1;
	paisa[1].y = 15;
	paisa[1].x = 104;
	paisa[1].state = 1;
	paisa[1].num = 1;
	paisa[2].y = 15;
	paisa[2].x = 112;
	paisa[2].state = 1;
	paisa[2].num = 1;
	paisa[3].y = 10;
	paisa[3].x = 108;
	paisa[3].state = 1;
	paisa[3].num = 1;
	paisa[4].y = 12;
	paisa[4].x = 252;
	paisa[4].state = 0;
	paisa[4].num = 1;
	paisa[5].y = 14;
	paisa[5].x = 333;
	paisa[5].state = 1;
	paisa[5].num = 1;
	paisa[6].y = 8;
	paisa[6].x = 397;
	paisa[6].state = 1;
	paisa[6].num = 1;
	paisa[7].y = 15;
	paisa[7].x = 421;
	paisa[7].state = 1;
	paisa[7].num = 1;
	paisa[8].y = 15;
	paisa[8].x = 441;
	paisa[8].state = 1;
	paisa[8].num = 1;
	paisa[9].y = 15;
	paisa[9].x = 451;
	paisa[9].state = 1;
	paisa[9].num = 1;
	paisa[10].y = 15;
	paisa[10].x = 461;
	paisa[10].state = 1;
	paisa[10].num = 1;
	paisa[11].y = 8;
	paisa[11].x = 451;
	paisa[11].state = 1;
	paisa[11].num = 1;
	paisa[12].y = 8;
	paisa[12].x = 521;
	paisa[12].state = 1;
	paisa[12].num = 1;
	paisa[13].y = 8;
	paisa[13].x = 525;
	paisa[13].state = 1;
	paisa[13].num = 1;
	paisa[14].y = 14;
	paisa[14].x = 716;
	paisa[14].state = 1;
	paisa[14].num = 1;
	support[0].y = 5 * 24 / 6;
	support[0].x = 0;
	support[0].rows = 24 - (5 * 24 / 6 );
	support[0].cols = 1000;
	giro[0].rows = 4;
	giro[0].cols = 12;
	giro[0].y = 5 * 24 / 6;
	giro[0].x = 287;
	giro[1].rows = 4;
	giro[1].cols = 16;
	giro[1].y = 5 * 24 / 6;
	giro[1].x = 357;
	giro[2].rows = 4;
	giro[2].cols = 15;
	giro[2].y = 5 * 24 / 6;
	giro[2].x = 631;
	chado[0].rows = 6;
	chado[0].cols = 6;
	chado[0].y = 14;
	chado[0].x = 545;
	chado[0].color = 1;
	chado[1].rows = 6;
	chado[1].cols = 1;
	chado[1].y = 14;
	chado[1].x = 574;
	chado[1].color = 1;
	chado[2].rows = 5;
	chado[2].cols = 1;
	chado[2].y = 15;
	chado[2].x = 577;
	chado[2].color = 1;
	chado[3].rows = 4;
	chado[3].cols = 1;
	chado[3].y = 16;
	chado[3].x = 580;
	chado[3].color = 1;
	chado[4].rows = 3;
	chado[4].cols = 1;
	chado[4].y = 17;
	chado[4].x = 583;
	chado[4].color = 1;
	chado[5].rows = 2;
	chado[5].cols = 1;
	chado[5].y = 18;
	chado[5].x = 586;
	chado[5].color = 1;
	chado[6].rows = 1;
	chado[6].cols = 1;
	chado[6].y = 19;
	chado[6].x = 589;
	chado[6].color = 1;
	chado[7].rows = 6;
	chado[7].cols = 6;
	chado[7].y = 14;
	chado[7].x = 612;
	chado[7].color = 1;
	chado[8].rows = 6;
	chado[8].cols = 1;
	chado[8].y = 14;
	chado[8].x = 645;
	chado[8].color = 1;
	chado[9].rows = 5;
	chado[9].cols = 1;
	chado[9].y = 15;
	chado[9].x = 648;
	chado[9].color = 1;
	chado[10].rows = 4;
	chado[10].cols = 1;
	chado[10].y = 16;
	chado[10].x = 651;
	chado[10].color = 1;
	chado[11].rows = 3;
	chado[11].cols = 1;
	chado[11].y = 17;
	chado[11].x = 654;
	chado[11].color = 1;
	chado[12].rows = 2;
	chado[12].cols = 1;
	chado[12].y = 18;
	chado[12].x = 657;
	chado[12].color = 1;
	chado[13].rows = 1;
	chado[13].cols = 1;
	chado[13].y = 19;
	chado[13].x = 660;
	chado[13].color = 1;
	chado[14].rows = 15;
	chado[14].cols = 15;
	chado[14].y = 5;
	chado[14].x = 764;
	chado[14].color = 1;
	chado[15].rows = 15;
	chado[15].cols = 1;
	chado[15].y = 5;
	chado[15].x = 809;
	chado[15].color = 1;
	guso[0].height = 1;
	guso[0].state = 0;
	guso[0].y = 18;
	guso[0].x = 132;
	guso[1].height = 2;
	guso[1].state = 0;
	guso[1].y = 16;
	guso[1].x = 167;
	guso[2].height = 2;
	guso[2].state = 0;
	guso[2].y = 14;
	guso[2].x = 202;
	guso[3].height = 2;
	guso[3].state = 0;
	guso[3].y = 14;
	guso[3].x = 237;
	guso[4].height = 2;
	guso[4].state = 0;
	guso[4].y = 16;
	guso[4].x = 678;
	guso[5].height = 2;
	guso[5].state = 0;
	guso[5].y = 16;
	guso[5].x = 754;
	fp = open("level0-0", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);
	write(fp, &hash, sizeof(map));
	write(fp, &todo, sizeof(bricks) * hash.nb);
	write(fp, &paisa, sizeof(money) * hash.nm);
	write(fp, &guso, sizeof(pipes) * hash.np);
	write(fp, &support, sizeof(wall) * hash.nw);
	write(fp, &giro, sizeof(holes) * hash.nh);	
	write(fp, &chado, sizeof(stairs) * hash.ns);		
	close(fp);
}
	
