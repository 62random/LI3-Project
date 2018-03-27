#ifndef __MYLIST_H__
#define __MYLIST_H__

#include <stdlib.h>
#include <stdio.h>

typedef struct lligada{
	void * key;
	void * data;
	struct lligada * next;
}*LList;

typedef struct mylist{
	int (*f_compare)(void *,void *);
	void (*destroy_key)(void *);
	void (*destroy_data)(void *);
	LList lista;
}*MYLIST;

MYLIST init_MYLIST(void * f_comp,void * dest_key,void * dest_data);

void free_MYLIST(MYLIST r);

LList create_box(void * key,void * data);

int search_list(MYLIST pai,void * key);

MYLIST insere_list(MYLIST r,void * key,void * data);

void print_List(LList r);

#endif
