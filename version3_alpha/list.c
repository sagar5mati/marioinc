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
//Reads from a file into list
void readlist(list *l) {
	int count;
	FILE *fp;
	node *prev = (node *)malloc(sizeof(node));
	node *next = (node *)malloc(sizeof(node));
	fp = fopen("savelist", "r");
	if(!fp)
		return;	
	fscanf(fp, "%p %d ", &l->head, &l->count);
	l->head = NULL;
	count = l->count - 1;
	if(count == -1)
		count = 0;
	fscanf(fp, "%s %p", prev->name, &prev->next);
	l->head = prev;	
	while(count--) {
		fscanf(fp, "%s %p ", next->name, &next->next);
		next->next = NULL;
		prev->next = next;
		prev = next;
	}
	next->next = NULL;
	fclose(fp);
}
//Initializes the list structure
void initlist(list *l) {
	l->head = NULL;
	l->count = 0;
}
//Writes to a file the list
void writelist(list *l) {
	FILE *fp;
	node *t = l->head;
	fp = fopen("savelist", "w+");
	fprintf(fp, "%p %d ", l->head, l->count);
	while(t) {
		fprintf(fp, "%s %p ", t->name, t->next);
		t = t->next;
	}
	fclose(fp);
}
//Insert a element in a list
void insertl(list *l, int i, char *name) {
	node *n, *t;
	int j = 1;
	n = (node *)malloc(sizeof(node));
	strcpy(n->name, name);
	n->next = NULL;
	if(!l->head) {
		l->head = n;
		l->count++;
		return;
	}
	t = l->head;
	while(j + 1 < i && t) {
		t = t->next;
		j++;
	}
	if(i == 1) {
		n->next = l->head;
		l->head = n;
		l->count++;
		return;
	}
	n->next = t->next;
	t->next = n;
	l->count++;
}	
//Remove a element from a list
void removel(list *l, int i) {
	node *t = l->head, *s;
	int j = 1;
	if(!l->head && i == 1) {
		l->head = t->next;
		free(t);
		return;
	}
	while(j + 1 < i) {
		t = t->next;
		j++;
	}
	s = t->next;
	if(s)
		t->next = s->next;
	free(s);
	l->count--;
}
//View an element of a list
char *viewl(list *l, int i) {
	node *t = l->head;	
	int j = 1;
	while(j < i && t) {
		t = t->next;
		j++;
	}
	if(t)
		return t->name;
	return NULL;
} 	
//Check for empty list
int emptyl(list *l) {
	if(l->head)
		return 0;
	return 1;
}
