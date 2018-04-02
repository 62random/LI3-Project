#ifndef __MYTREE_H__
#define __MYTREE_H__

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>

typedef struct AVBin * AVL;
typedef struct tree  * TREE;

int 	TREE_balance		(TREE tre);
TREE 	insere_tree			(TREE gl, void * key, void * data);
TREE 	createTREE			(void * f_compare,void * destroy_key,void * destroy_data);
void 	freeTREE_AVL		(TREE tre);
void 	freeTREES_POSTS		(TREE postTreeId, TREE postTreeData);
void * 	search_AVL			(TREE tree, void * key,int * valid);
void 	count_nodes_With_Condition(TREE tree, void * data1, void * data2,void (*f_nodo)(void *,void *,void *),void * data3,void * data4);
int 	test_TREE_PROP		(TREE tree);
#endif
